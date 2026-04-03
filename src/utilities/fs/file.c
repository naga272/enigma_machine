
#include "utilities/stdlib/stdlib.h"
#include "utilities/memory/heap/malloc.h"
#include "utilities/fs/file.h"
#include "errors_no.h"
#include "config.h"


/*
* Gestisce i filesystem registrati e i file descriptor globali.
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


O3 static inline struct filesystem** fs_get_free_filesystem()
{
    int i = 0;
    for (i = 0; i < ENIGMAOS_MAX_FILESYSTEMS; i++)
        if (filesystems[i] == 0)
            return &filesystems[i];
    
    return 0;
}


void fs_insert_filesystem(struct filesystem* filesystem)
{
    struct filesystem** fs;

    if (filesystem == 0)
        set_message_x_panic((uchar*) "EINVARG! module file.c foo fs_insert_filesystem");

    fs = fs_get_free_filesystem();

    if (!fs)
        set_message_x_panic((uchar*) "Problem inserting filesystem! module file.c");

    *fs = filesystem;

}


static inline void fs_static_load()
{
    // fs_insert_filesystem(fat16_init());
}


void fs_load()
{
    memset(filesystems, 0x00, sizeof(filesystems));
    fs_static_load();
}


void fs_init()
{
    memset(file_descriptors, 0x00, sizeof(file_descriptors));
}


static inline i32 file_new_descriptor(struct file_descriptor** desc_out)
{
    i32 res = -ENOMEM;
    for (i32 i = 0; i < ENIGMAOS_MAX_FILE_DESCRIPTORS; i++) {
        if (file_descriptors[i] == 0) {
            struct file_descriptor* desc = kcalloc(sizeof(struct file_descriptor));
            desc->index = i + 1;
            file_descriptors[i] = desc;
            *desc_out = desc;
            res = 0;
            break;
        }
    }

    return res;
}


static struct file_descriptor* file_get_descriptor(i32 fd)
{
    if (fd <= 0 || fd >= ENIGMAOS_MAX_FILE_DESCRIPTORS)
        return 0;
    
    i32 index = fd - 1;
    return file_descriptors[index];
}


struct filesystem* fs_resolve(struct disk* disk) 
{
    struct filesystem* fs = 0;
    for (i32 i = 0; i < ENIGMAOS_MAX_FILESYSTEMS; i++) {
        if (filesystems[i] != 0 && filesystems[i]->resolve(disk) == 0) {
            fs = filesystems[i];
            break;
        }
    }

    return fs;
}


i32 fopen(const char* filename, const char* mode)
{
    return -EIO;
}