
#include "utilities/string/string.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/fs/fat/fat16.h"
#include "utilities/disk/disk.h"
#include "utilities/disk/streamer.h"
#include "errors_no.h"
#include "config.h"


/* NOT YET READY */

extern void set_message_x_panic(uchar* msg);
i32 fat16_resolve(struct disk* disk);
void* fat16_open(struct disk* disk, struct path_part* path, FILE_MODE mode);


extern void print_hex(size_t);
extern int kprintf(const char*, ...);

#define ENIGMAOS_FAT16_SIGNATURE 0x29
#define ENIGMAOS_FAT16_ENTRY_SIZE 0x02
#define ENIGMAOS_FAT16_BAD_SECTOR 0xFF7
#define ENIGMAOS_FAT16_UNUSED 0x00

typedef u32 FAT_ITEM_TYPE;
#define FAT_ITEM_TYPE_DIRECTORY 0
#define FAT_ITEM_TYPE_FILE 1

// fat directory entry attributes bit mask
#define FAT_FILE_READ_ONLY 0x01
#define FAT_FILE_HIDDEN 0x02
#define FAT_FILE_SYSTEM 0x04
#define FAT_FILE_VOLUME_LABEL 0x08
#define FAT_FILE_SUBDIRECTORY 0x10
#define FAT_FILE_ARCHIVED 0x20
#define FAT_FILE_DEVICE 0x40
#define FAT_FILE_RESERVED 0x80


/*
*  struct fat_header_extended
*  @drive_number -> numero logico del drive utilizzato dal BIOS
*  @win_nt_bit -> campo riservato usato da Windows NT
*  @signature -> firma utilizzata per identificare la validità del boot record
*  @volume_id -> identificatore univoco del volume
*  @volume_id_string -> etichetta del volume composta da 11 caratteri
*  @system_id_string -> stringa identificativa del filesystem
*
*  Contiene i campi estesi del boot sector FAT, utilizzati per
*  informazioni aggiuntive come identificatore del volume,
*  etichetta e firma del filesystem.
*/
struct fat_header_extended
{
    u8 drive_number;
    u8 win_nt_bit;
    u8 signature;
    u32 volume_id;
    u8 volume_id_string[11];
    u8 system_id_string[8];
} __attribute__((packed));


/*
*  struct fat_header
*  @short_jmp_ins -> istruzione di salto iniziale del bootloader
*  @oem_identifier -> identificatore OEM del filesystem
*  @bytes_per_sector -> numero di byte presenti in un settore
*  @sectors_per_cluster -> numero di settori che compongono un cluster
*  @reserved_sectors -> numero di settori riservati prima della FAT
*  @fat_copies -> numero di copie della File Allocation Table
*  @root_dir_entries -> numero massimo di entry nella root directory
*  @number_of_sectors -> numero totale di settori se il disco è piccolo
*  @media_type -> tipo di supporto fisico
*  @sectors_per_fat -> numero di settori occupati da una FAT
*  @sectors_per_track -> numero di settori per traccia del disco
*  @number_of_heads -> numero di testine del disco
*  @hidden_setors -> numero di settori nascosti prima della partizione
*  @sectors_big -> numero totale di settori per dischi di grandi dimensioni
*
*  Rappresenta l'header principale del boot sector FAT. Contiene
*  tutte le informazioni necessarie per interpretare la struttura
*  fisica e logica del filesystem sul disco.
*/
struct fat_header
{
    u8 short_jmp_ins[3];
    u8 oem_identifier[8];
    u16 bytes_per_sector;
    u8 sectors_per_cluster;
    u16 reserved_sectors;
    u8 fat_copies;
    u16 root_dir_entries;
    u16 number_of_sectors;
    u8 media_type;
    u16 sectors_per_fat;
    u16 sectors_per_track;
    u16 number_of_heads;
    u32 hidden_setors;
    u32 sectors_big;
} __attribute__((packed));


/*
*  struct fat_h
*  @primary_header -> header principale del filesystem FAT
*  @shared -> unione contenente i dati estesi dell'header FAT
*
*  Rappresenta l'intero header FAT letto dal boot sector del disco,
*  unendo i campi standard e quelli estesi in un'unica struttura.
*/
struct fat_h
{
    struct fat_header primary_header;
    union fat_h_e {
        struct fat_header_extended extended_header;
    } shared;
};


/*
*  struct fat_directory_item
*  @filename -> nome del file in formato 8 caratteri
*  @ext -> estensione del file in formato 3 caratteri
*  @attribute -> attributi del file o directory
*  @reserved -> byte riservato
*  @creation_time_tenths_of_a_sec -> frazioni di secondo del tempo di creazione
*  @creation_time -> orario di creazione del file
*  @creation_date -> data di creazione del file
*  @last_access -> data dell'ultimo accesso
*  @high_16_bits_first_cluster -> parte alta del cluster iniziale
*  @last_mod_time -> orario dell'ultima modifica
*  @last_mod_date -> data dell'ultima modifica
*  @low_16_bits_first_cluster -> parte bassa del cluster iniziale
*  @filesize -> dimensione del file in byte
*
*  Rappresenta una singola entry presente in una directory FAT.
*  Può descrivere sia un file sia una sottodirectory.
*/
struct fat_directory_item
{
    u8 filename[8];
    u8 ext[3];
    u8 attribute;
    u8 reserved;
    u8 creation_time_tenths_of_a_sec;
    u16 creation_time;
    u16 creation_date;
    u16 last_access;
    u16 high_16_bits_first_cluster;
    u16 last_mod_time;
    u16 last_mod_date;
    u16 low_16_bits_first_cluster;
    u32 filesize;
} __attribute__((packed));


/*
*  struct fat_directory
*  @item -> array di elementi presenti nella directory
*  @total -> numero totale di elementi presenti
*  @sector_pos -> settore iniziale della directory sul disco
*  @ending_sector_pos -> ultimo settore occupato dalla directory
*
*  Rappresenta una directory FAT già caricata in memoria, contenente
*  le sue entry e le informazioni sulla posizione occupata sul disco.
*/
struct fat_directory
{
    struct fat_directory_item* item;
    i32 total;
    i32 sector_pos;
    i32 ending_sector_pos;
};


/*
*  struct fat_item
*  @item -> puntatore a una entry di file o directory FAT
*  @directory -> puntatore a una directory FAT caricata in memoria
*  @type -> tipo dell'elemento, usato per distinguere file e directory
*
*  Rappresenta un elemento generico del filesystem FAT. Tramite
*  l'union può contenere sia un file sia una directory.
*/
struct fat_item
{
    union {
        struct fat_directory_item* item;
        struct fat_directory* directory;
    };

    FAT_ITEM_TYPE type;
};


/*
*  struct fat_item_descriptor
*  @item -> puntatore all'elemento FAT associato
*  @pos -> posizione corrente di lettura o scrittura all'interno dell'elemento
*
*  Mantiene lo stato di utilizzo di un file o directory FAT aperto,
*  inclusa la posizione corrente nel contenuto.
*/
struct fat_file_descriptor
{
    struct fat_item* item;
    u32 pos;
};


/*
*  struct fat_private
*  @header -> header completo del filesystem FAT
*  @root_directory -> root directory del filesystem caricata in memoria
*  @cluster_read_stream -> stream utilizzato per leggere i cluster dei file
*  @fat_read_stream -> stream utilizzato per leggere la File Allocation Table
*  @directory_stream -> stream utilizzato per leggere le directory
*
*  Contiene tutti i dati privati necessari al driver FAT per gestire
*  il filesystem, inclusi header, root directory e stream di lettura.
*/
struct fat_private
{
    struct fat_h header;
    struct fat_directory root_directory;
    struct disk_stream* cluster_read_stream;
    struct disk_stream* fat_read_stream;
    struct disk_stream* directory_stream;
};


struct filesystem fat16_fs = {
    .resolve = fat16_resolve,
    .open = fat16_open,
};


struct filesystem* fat16_init()
{
    strcpy(fat16_fs.name, "FAT16");
    return &fat16_fs;
}


static inline ainline void fat16_init_private(struct disk* disk, struct fat_private* private)
{
    memset(private, 0, sizeof(struct fat_private));
    private->cluster_read_stream = diskstreamer_new(disk->id);
    private->fat_read_stream = diskstreamer_new(disk->id);
    private->directory_stream = diskstreamer_new(disk->id);
}


i32 fat16_sector_to_absolute(struct disk* disk, i32 sector)
{
    return sector * disk->sector_size;
}


i32 fat16_get_total_items_for_directory(struct disk* disk, u32 directory_start_sector)
{
    struct fat_directory_item item;
    struct fat_directory_item empty_item;
    memset(&empty_item, 0, sizeof(empty_item));
    
    struct fat_private* fat_private = disk->fs_private;

    i32 res = 0;
    i32 i = 0;
    i32 directory_start_pos = directory_start_sector * disk->sector_size;
    struct disk_stream* stream = fat_private->directory_stream;

    if (diskstreamer_seek(stream, directory_start_pos) != EXIT_SUCCESS) {
        res = -EIO;
        goto out;
    }

    while (1) {
        if (diskstreamer_read(stream, &item, sizeof(item)) != EXIT_SUCCESS) {
            res = -EIO;
            goto out;
        }

        // end
        if (item.filename[0] == 0x00)
            break;

        // forse unused (?)
        if (item.filename[0] == 0xE5)
            continue;

        i++;
    }

    res = i;

out:
    return res;
}


O3 i32 fat16_get_root_directory(struct disk* disk, struct fat_private* fat_private, struct fat_directory* directory)
{
    i32 res = 0;
    
    struct fat_header* primary_header = &fat_private->header.primary_header;
    
    i32 root_dir_sector_pos = (primary_header->fat_copies * primary_header->sectors_per_fat) + primary_header->reserved_sectors;
    i32 root_dir_entries = fat_private->header.primary_header.root_dir_entries;
    i32 root_dir_size = (root_dir_entries * sizeof(struct fat_directory_item));
    i32 total_sectors = root_dir_size / disk->sector_size;
    
    if (root_dir_size % disk->sector_size)
        total_sectors += 1;

    i32 total_items = fat16_get_total_items_for_directory(disk, root_dir_sector_pos);

    struct fat_directory_item* dir = kcalloc(root_dir_size);
    
    if (!dir) {
        res = -ENOMEM;
        goto out;
    }

    struct disk_stream* stream = fat_private->directory_stream;
    if (diskstreamer_seek(stream, fat16_sector_to_absolute(disk, root_dir_sector_pos)) != EXIT_SUCCESS) {
        res = -EIO;
        goto out;
    }

    if (diskstreamer_read(stream, dir, root_dir_size) != EXIT_SUCCESS) {
        res = -EIO;
        goto out;
    }

    directory->item = dir;
    directory->total = total_items;
    directory->sector_pos = root_dir_sector_pos;
    directory->ending_sector_pos = root_dir_sector_pos + (root_dir_size / disk->sector_size);
out:
    return res;
}


i32 fat16_resolve(struct disk* disk)
{
    i32 res = 0;

    struct fat_private* fat_private = kcalloc(sizeof(struct fat_private));
    fat16_init_private(disk, fat_private);

    disk->fs_private = fat_private;
    disk->filesystem = &fat16_fs;
    
    struct disk_stream* stream = diskstreamer_new(disk->id);
    if (!stream) {
        res = -ENOMEM;
        goto out;
    }

    if (diskstreamer_read(stream, &fat_private->header, sizeof(fat_private->header)) != EXIT_SUCCESS) {
        res = -EIO;
        goto out;
    }

    if (fat_private->header.shared.extended_header.signature != 0x29) {
        res = -1;
        goto out;
    }

    if (fat16_get_root_directory(disk, fat_private, &fat_private->root_directory) != EXIT_SUCCESS) {
        res = -EIO;
        goto out;
    }

out:
    if (stream)
        diskstreamer_close(stream);

    if (res < 0) {
        kfree(fat_private);
        disk->fs_private = 0;
    }
    return res;
}


void fat16_to_proper_string(char** out, const char* in)
{
    while (*in != 0x00 && *in != 0x20) {
        **out = *in;
        *out += 1;
        in +=1;
    }

    if (*in == 0x20)
        **out = 0x00;
}


void fat16_get_full_relative_filename(struct fat_directory_item* item, char* out, i32 max_len)
{
    memset(out, 0x00, max_len);

    char *out_tmp = out;

    fat16_to_proper_string(&out_tmp, (const char*) item->filename);

    if (item->ext[0] != 0x00 && item->ext[0] != 0x20) {
        *out_tmp++ = '.';
        fat16_to_proper_string(&out_tmp, (const char*) item->ext);
    }

}


struct fat_directory_item* fat16_clone_directory_item(struct fat_directory_item* item, i32 size)
{
    struct fat_directory_item* item_copy = 0;

    if (size < sizeof(struct fat_directory_item))
        return 0;
    
    item_copy = kcalloc(size);
    if (!item_copy)
        return 0;
    
    memcpy(item_copy, item, size);
    return item_copy;
}


O3 static inline ainline u32 fat16_get_first_cluster(struct fat_directory_item* item)
{
    return (item->high_16_bits_first_cluster) | item->low_16_bits_first_cluster;
};


O3 static inline ainline i32 fat16_cluster_to_sector(struct fat_private* private, i32 cluster)
{
    return private->root_directory.ending_sector_pos + ((cluster - 2) * private->header.primary_header.sectors_per_cluster);
}


O3 static inline ainline u32 fat16_get_first_fat_sector(struct fat_private* private)
{
    return private->header.primary_header.reserved_sectors;
}


O3 static inline ainline i32 fat16_get_fat_entry(struct disk* disk, i32 cluster)
{
    i32 res = -1;
    struct fat_private* private = disk->fs_private;
    struct disk_stream* stream = private->fat_read_stream;
    
    if (!stream)
        goto out;

    u32 fat_table_position = fat16_get_first_fat_sector(private) * disk->sector_size;
    res = diskstreamer_seek(stream, fat_table_position * (cluster * ENIGMAOS_FAT16_ENTRY_SIZE));
    if (res < 0)
        goto out;

    u16 result = 0;
    res = diskstreamer_read(stream, &result, sizeof(result));
    
    if (res < 0)
        goto out;
    
    
    res = result;
out:
    return res;
}


static i32 fat16_get_cluster_for_offset(struct disk *disk, i32 starting_cluster, i32 offset)
{
    i32 res = 0;
    struct fat_private *private = disk->fs_private;
    i32 size_of_cluster_bytes = private->header.primary_header.sectors_per_cluster * disk->sector_size;
    i32 cluster_to_use = starting_cluster;
    i32 clusters_ahead = offset / size_of_cluster_bytes;
    for (i32 i = 0; i < clusters_ahead; i++)
    {
        i32 entry = fat16_get_fat_entry(disk, cluster_to_use);
        if (entry == 0xFFf8 || entry == 0xFFFF) {
            // We are at the last entry in the file
            res = -EIO;
            goto out;
        }

        // Sector is marked as bad?
        if (entry == 0xFF7) {
            res = -EIO;
            goto out;
        }

        // Reserved sector?
        if (entry == 0xFF0 || entry == 0xFF6) {
            res = -EIO;
            goto out;
        }

        if (entry == 0x00) {
            res = -EIO;
            goto out;
        }

        cluster_to_use = entry;
    }

    res = cluster_to_use;
out:
    return res;
}


O3 static inline ainline i32 fat16_read_internal_from_stream(struct disk* disk, struct disk_stream* stream, i32 cluster, i32 offset, i32 total, void* out)
{
    i32 res = 0;
    struct fat_private* private = disk->fs_private;
    i32 size_of_cluster_bytes = private->header.primary_header.sectors_per_cluster * disk->sector_size;
    i32 cluster_to_use = fat16_get_cluster_for_offset(disk, cluster, offset);
    
    if (cluster_to_use < 0) {
        res = cluster_to_use;
        goto out;
    }

    i32 offset_from_cluster = offset % size_of_cluster_bytes;

    i32 starting_sector = fat16_cluster_to_sector(private, cluster_to_use);
    i32 starting_pos = (starting_sector * disk->sector_size) + offset_from_cluster;
    i32 total_to_read = total > size_of_cluster_bytes ? size_of_cluster_bytes : total;

    // here there is a bug to fix, don't touch this goto
    // i need to debug the next code and find the bug
    goto out;

    res = diskstreamer_seek(stream, starting_pos);
    if (res != 0)
        goto out;
    
    res = diskstreamer_read(stream, out, total_to_read);
    if (res != 0)
        goto out;

    total -= total_to_read;
    // We still have more to read
    if (total > 0)
        res = fat16_read_internal_from_stream(disk, stream, cluster, offset+total_to_read, total, out + total_to_read);

out:
    return res;
}


O3 static inline ainline i32 fat16_read_internal(struct disk* disk, i32 starting_cluster, i32 offset, i32 total, void* out)
{
    struct fat_private* fs_private = disk->fs_private;
    struct disk_stream* stream = fs_private->cluster_read_stream;

    return fat16_read_internal_from_stream(disk, stream, starting_cluster, offset, total, out);
}


void fat16_free_directory(struct fat_directory* directory)
{
    if (!directory)
        return;

    if (directory->item)
        kfree(directory->item);

    kfree(directory);
}


void fat16_fat_item_free(struct fat_item* item)
{
    if (item->type == FAT_ITEM_TYPE_DIRECTORY)
        fat16_free_directory(item->directory);

    else if(item->type == FAT_ITEM_TYPE_FILE)
        kfree(item->item);

    kfree(item);
}


struct fat_directory* fat16_load_fat_directory(struct disk* disk, struct fat_directory_item* item)
{
    i32 res = 0;
    struct fat_directory* directory = 0;
    struct fat_private* fat_private = disk->fs_private;

    if (!(item->attribute & FAT_FILE_SUBDIRECTORY)) {
        res = -EINVARG;
        goto out;
    }

    directory = kcalloc(sizeof(struct fat_directory));
    if (!directory) {
        res = -ENOMEM;
        goto out;
    }

    i32 cluster = fat16_get_first_cluster(item);
    i32 cluster_sector = fat16_cluster_to_sector(fat_private, cluster);
    i32 total_items = fat16_get_total_items_for_directory(disk, cluster_sector);
    
    directory->total = total_items;
    
    i32 directory_size = directory->total * sizeof(struct fat_directory_item);
    
    directory->item = kcalloc(directory_size);
    
    if (!directory->item) {
        res = -ENOMEM;
        goto out;
    }

    res = fat16_read_internal(disk, cluster, 0x00, directory_size, directory->item);
    if (res != EXIT_SUCCESS)
        goto out;

out:
    if (res != EXIT_SUCCESS)
        fat16_free_directory(directory);

    return directory;
}


struct fat_item* fat16_new_fat_item_for_directory_item(struct disk* disk, struct fat_directory_item* item)
{
    struct fat_item* f_item = kcalloc(sizeof(struct fat_item));
    if (!f_item)
        return 0;

    if (item->attribute & FAT_FILE_SUBDIRECTORY) {
        f_item->directory = fat16_load_fat_directory(disk, item);
        f_item->type = FAT_ITEM_TYPE_DIRECTORY;
    }

    f_item->type = FAT_ITEM_TYPE_FILE;
    f_item->item = fat16_clone_directory_item(item, sizeof(struct fat_directory_item));
    return f_item;
}


struct fat_item* fat16_find_item_in_directory(struct disk* disk, struct fat_directory* directory, const char* name)
{
    struct fat_item* f_item = 0;
    char tmp_filename[KERNEL_FS_MAX_PATH];

    for (size_t i = 0; i < directory->total; i++) {
        fat16_get_full_relative_filename(&directory->item[i], tmp_filename, sizeof(tmp_filename));

        // vado a creare un nuovo fat_item quando trovato
        if (istrncmp(tmp_filename, name, sizeof(tmp_filename)) == 0)
            f_item = fat16_new_fat_item_for_directory_item(disk, &directory->item[i]);
    }

    return f_item;
}


struct fat_item* fat16_get_directory_entry(struct disk* disk, struct path_part* path)
{
    struct fat_private* fat_private = disk->fs_private;
    struct fat_item* current_item = 0;
    struct fat_item* root_item = fat16_find_item_in_directory(
        disk,
        &fat_private->root_directory,
        path->part
    );

    if (!root_item)
        goto out;

    struct path_part* next_part = path->next;
    current_item = root_item;
    while (next_part != 0) {
        if (current_item->type != FAT_ITEM_TYPE_DIRECTORY) {
            current_item = 0;
            break;
        }

        struct fat_item* tmp_item = fat16_find_item_in_directory(
            disk,
            current_item->directory,
            next_part->part
        );
        
        fat16_fat_item_free(current_item);
        current_item = tmp_item;
        next_part = next_part->next;
    }
out:
    return current_item;
}


void* fat16_open(struct disk* disk, struct path_part* path, FILE_MODE mode)
{
    if (mode != FILE_MODE_READ)
        return (void*) -1;

    struct fat_file_descriptor* descriptor = 0;
    descriptor = kcalloc(sizeof(struct fat_file_descriptor));

    if (!descriptor)
        return (void*) -ENOMEM;

    descriptor->item = fat16_get_directory_entry(disk, path);
    
    if (!descriptor->item)
        return (void*) -EIO;

    descriptor->pos = 0;
    return descriptor;
}
