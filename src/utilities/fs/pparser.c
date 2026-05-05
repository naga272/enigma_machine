
#include "utilities/fs/pparser.h"
#include "utilities/string/string.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/memory/heap/malloc.h"
#include "errors_no.h"
#include "utilities/video/video.h"


static i32 pathparser_path_valid_format(const char* filename)
{
    i32 len = strnlen(filename, KERNEL_FS_MAX_PATH);
    return (len >= 3 && isdigit(filename[0]) && memcmp((void*) &filename[1], ":/", 2) == 0);
}


O3 static inline i32 pathparser_get_drive_by_path(const char** path)
{
    /*
    *   @path: puntatore al puntatore del path da elaborare
    *
    *   Estrae il numero del drive presente all'inizio del path.
    *   Se il formato del path non è valido restituisce un errore.
    *   Dopo aver letto il numero del drive, avanza il puntatore
    *   oltre la parte iniziale "0:/".
    */
    if (!pathparser_path_valid_format(*path)) {
        return -1;
    }

    i32 drive_no = tonumericdigit(*path[0]);

    // Add 3 bytes to skip drive number 0:/ 1:/ 2:/
    *path += 3;
    return drive_no;
}


O3 static inline struct path_root* pathparser_create_root(i32 drive_number)
{
    /*
    *   @drive_number: numero identificativo del drive associato al path
    *
    *   Alloca e inizializza una struttura path_root contenente il
    *   numero del drive e il puntatore iniziale alla lista delle
    *   parti del path.
    */
    struct path_root* path_r = kcalloc(sizeof(struct path_root));

    path_r->drive_no = drive_number;
    path_r->first = 0;
    return path_r;
}


O3 static inline const char* pathparser_get_path_part(const char** path)
{
    /*
    *   @path: puntatore al puntatore del path da elaborare
    *
    *   Estrae una singola parte del path fino al prossimo slash o
    *   alla fine della stringa. Ad ogni chiamata restituisce una
    *   nuova porzione del path e avanza il puntatore originale.
    *   es:
    *   path = bin/bash.bin 
    *   char* porzione = pathparser_get_path_part(path);    // porzione = "bin"
    *   porzione = pathparser_get_path_part(porzione);      // porzione = "bash.bin"
    **/

    char* result_path_part = kcalloc(KERNEL_FS_MAX_PATH);
    if (result_path_part == 0)
        print((uchar*) "error nell'allocare result_path_part\n");

    int i = 0;
    while (**path != '/' && **path != 0x00) {
        result_path_part[i] = **path;
        *path += 1;
        i++;
    }

    if (**path == '/') {
        // Skip the forward slash to avoid problems
        *path += 1;
    }

    if (i == 0) {
        kfree(result_path_part);
        result_path_part = 0;
    }

    return result_path_part;
}


O3 struct path_part* pathparser_parse_path_part(struct path_part* last_part, const char** path)
{
    /*
    *   @last_part: ultimo nodo della lista concatenata già creato
    *   @path: puntatore al puntatore del path da elaborare
    *
    *   Crea una nuova struttura path_part contenente la prossima
    *   parte del path. Se esiste un nodo precedente, collega il
    *   nuovo nodo alla lista concatenata.
    */
    const char* path_part_str = pathparser_get_path_part(path);
    if (!path_part_str) {
        print((uchar*) "error in pathparser_get_path_part\n");
        return 0;
    }

    struct path_part* part = kcalloc(sizeof(struct path_part));
    if (!path_part_str) {
        print((uchar*) "error in path_part* part\n");
        return 0;
    }
    part->part = path_part_str;
    part->next = 0x00;

    if (last_part)
        last_part->next = part;

    return part;
}


O3 void pathparser_free(struct path_root* root)
{
    /*
    *   @root: struttura path_root da liberare
    *
    *   Libera tutta la memoria associata alla struttura path_root,
    *   incluse tutte le parti del path presenti nella lista concatenata.
    */
    struct path_part* part = root->first;
    while (part) {
        struct path_part* next_part = part->next;
        kfree((void*) part->part);
        kfree(part);
        part = next_part;
    }

    kfree(root);
}


O3 struct path_root* pathparser_parse(const char* path, const char* current_dir)
{
    /*
    *   @path: path assoluto da convertire in una struttura interna
    *   @current_dir: directory corrente utilizzata per eventuali path relativi
    *
    *   Analizza il path ricevuto, estrae il numero del drive e divide
    *   il resto del path nelle sue singole componenti. Restituisce una
    *   struttura path_root contenente il drive e una lista concatenata
    *   delle directory o file presenti nel path.
    */
    int res = 0;
    const char* tmp_path = path;
    struct path_root* path_root = 0;

    if (strlen(path) > KERNEL_FS_MAX_PATH)
        goto out;

    res = pathparser_get_drive_by_path(&tmp_path);
    if (res < 0) {
        print((uchar*) "error in pathparser_get_drive_by_path\n");
        goto out;
    }

    path_root = pathparser_create_root(res);

    struct path_part* first_part = pathparser_parse_path_part(NULL, &tmp_path);
    if (!first_part) {
        print((uchar*) "error in pathparser_parse_path_part\n");
        goto out;
    }

    path_root->first = first_part;
    struct path_part* part = pathparser_parse_path_part(first_part, &tmp_path);
    while (part) {
        part = pathparser_parse_path_part(part, &tmp_path);
    }
    
out:
    return path_root;
}