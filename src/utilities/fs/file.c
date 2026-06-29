
#include "utilities/stdlib/stdlib.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/fs/file.h"
#include "utilities/fs/fat/fat16.h"
#include "utilities/fs/pparser.h"
#include "utilities/string/string.h"
#include "utilities/disk/disk.h"
#include "errors_no.h"
#include "config.h"
#include "utilities/video/video.h"

extern void print_hex(size_t);
extern int kprintf(const char*, ...);


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("gestione dei filesystem registrati e i file descriptor globali.");


/* VFS
*
* Memorizza:
*   - la lista dei filesystem disponibili nel kernel
*   - la tabella dei file descriptor aperti
*
* Permette di:
*   - trovare uno slot libero per registrare un filesystem
*   - registrare un nuovo filesystem
*   - inizializzare e caricare i filesystem supportati
*   - creare nuovi file descriptor
*   - recuperare un file descriptor dato il suo fd
*   - individuare quale filesystem appartiene a un disco
*   - aprire file tramite fopen()
*
* fs_resolve() prova ogni filesystem registrato finché uno di essi
* riconosce il disco specificato.
* file_new_descriptor() assegna un nuovo indice fd e salva il
* descrittore nella tabella globale.
*/


extern void set_message_x_panic(uchar* msg);

struct filesystem* filesystems[ENIGMAOS_MAX_FILESYSTEMS];
struct file_descriptor* file_descriptors[ENIGMAOS_MAX_FILE_DESCRIPTORS];

O3 ainline struct filesystem** fs_get_free_filesystem()
{
    i32 i = 0;
    for (i = 0; i < ENIGMAOS_MAX_FILESYSTEMS; i++)
        if (filesystems[i] == 0)
            return &filesystems[i];

    return 0;
}


void fs_insert_filesystem(struct filesystem* filesystem)
{
    struct filesystem** fs;
    fs = fs_get_free_filesystem();
    if (!fs) {
        set_message_x_panic((uchar*) "Problem inserting filesystem"); 
        while (1) { }
    }

    *fs = filesystem;
}


O3 ainline void fs_static_load()
{
    fs_insert_filesystem(fat16_init());
}


void fs_load()
{
    memset(filesystems, 0, sizeof(filesystems));
    fs_static_load();
}


void fs_init()
{
    memset(file_descriptors, 0, sizeof(file_descriptors));
    fs_load();
}


O3 ainline i32 file_new_descriptor(struct file_descriptor** desc_out)
{
    i32 res = -ENOMEM;
    for (i32 i = 0; i < ENIGMAOS_MAX_FILE_DESCRIPTORS; i++) {
        if (file_descriptors[i] == 0) {
            struct file_descriptor* desc = kcalloc(sizeof(struct file_descriptor));
            // Descriptors start at 1
            desc->index = i + 1;
            file_descriptors[i] = desc;
            *desc_out = desc;
            res = 0;
            break;
        }
    }

    return res;
}


O3 ainline struct file_descriptor* file_get_descriptor(i32 fd)
{
    if (fd <= 0 || fd >= ENIGMAOS_MAX_FILE_DESCRIPTORS)
        return 0;

    // Descriptors start at 1
    i32 index = fd - 1;
    return file_descriptors[index];
}


struct filesystem* fs_resolve(struct disk* disk)
{
    struct filesystem* fs = 0;

    for (int i = 0; i < ENIGMAOS_MAX_FILESYSTEMS; i++) {
        if (filesystems[i] != 0 && filesystems[i]->resolve(disk) == 0) {
            fs = filesystems[i];
            break;
        }
    }
    print_hex((size_t) fs);
    return fs;
}


FILE_MODE file_get_mode_by_string(const char* str)
{
    FILE_MODE mode = FILE_MODE_INVALID;

    if (strncmp(str, "r", 1) == 0)
        mode = FILE_MODE_READ;
    else if(strncmp(str, "w", 1) == 0)
        mode = FILE_MODE_WRITE;
    else if(strncmp(str, "a", 1) == 0)
        mode = FILE_MODE_APPEND;

    return mode;
}


i32 fopen(const char* filename, const char* mode_str)
{
    i32 res = 0;
    struct path_root* root_path = pathparser_parse(filename, NULL);

    if (!root_path) {
        print((uchar*) "root path invalid\n");
        res = -EINVARG;
        goto out;
    }

    // We cannot have just a root path with 0:/
    if (!root_path->first) {
        kprintf("We cannot have just a root path with 0:/\n");
        res = -EINVARG;
        goto out;
    }

    // Ensure the disk we are reading from exists
    struct disk* disk = disk_get(root_path->drive_no);
    if (!disk) {
        kprintf("Ensure the disk we are reading from exists\n");
        res = -EIO;
        goto out;
    }

    if (!disk->filesystem) {
        kprintf("!disk->filesystem\n");
        res = -EIO;
        goto out;
    }

    FILE_MODE mode = file_get_mode_by_string(mode_str);
    if (mode == FILE_MODE_INVALID) {
        res = -EINVARG;
        goto out;
    }

    void* descriptor_private_data = disk->filesystem->open(disk, root_path->first, mode);
    if ((i32) descriptor_private_data < 0) {
        res = (i32) descriptor_private_data;
        goto out;
    }

    struct file_descriptor* desc = 0;
    res = file_new_descriptor(&desc);
    
    if (res < 0)
        goto out;

    desc->filesystem = disk->filesystem;
    desc->private = descriptor_private_data;
    desc->disk = disk;
    res = desc->index;

out:
    // fopen shouldnt return negative values
    if (res < 0)
        res = 0;

    return res;
}


i32 fread(void* ptr, u32 size, u32 nmemb, i32 fd)
{
    i32 res = 0;
    if (size == 0 || nmemb == 0 || fd < 1)
    {
        res = -EINVARG;
        goto out;
    }

    struct file_descriptor* desc = file_get_descriptor(fd);
    if (!desc)
    {
        res = -EINVARG;
        goto out;
    }

    res = desc->filesystem->read(desc->disk, desc->private, size, nmemb, (char*) ptr);
out:
    return res;
}