
#include "utilities/fs/pparser.h"
#include "utilities/string/string.h"
#include "utilities/stdlib/stdlib.h"
#include "utilities/memory/heap/malloc.h"
#include "errors_no.h"


/*
* Path parser module
* *** */


O3 static inline i32 pathparser_valid_format(const char* path)
{
    // check pattern like "0:/"
    i32 len = strnlen(path, KERNEL_FS_MAX_PATH);
    return (
        len >= 3 &&
        isdigit(path[0]) &&
        memcmp((void*) &path[1], ":/", 2)
    ) == 0;
}


O3 static inline i32 pathparser_get_drive_by_path(const char** path)
{
    // estrae il drive number dal path
    if (!pathparser_valid_format(*path))
        return -ENOENT;
    
    int drive_no = tonumericdigit(*path[0]);

    /*
    * skippo i primi 3 bytes ("0:/")
    * da: 0:/lorem.txt a lorem.txt
    */
    *path += 3;

    return drive_no;
}


O3 static inline struct path_root* pathparser_create_root(i32 drive_number)
{
    struct path_root* path_r = (struct path_root*) kcalloc(sizeof(struct path_root));
    path_r->drive_no = drive_number;
    path_r->first = 0;
    return path_r;
}


O3 static inline const char* pathparser_get_path_part(const char** path)
{
    /*
     * Ok, quello che stiamo facendo qui e' questo:
     * path = bin/bash.bin
     * alla prima chiamata di questa funzione viene restituito "bin";
     * alla seconda chiamata di questa funzione viene restituito "bash.bin"
     *  * */

    char* result_path_part = kcalloc(sizeof(KERNEL_FS_MAX_PATH));
    i32 i = 0;

    while (**path != '/' && **path != 0x00) {
        result_path_part[i] = **path;
        *path += 1;
        i++;
    }

    // skippo lo slash
    if (**path == '/')
        *path += 1;
    
    if (!i) {
        kfree(result_path_part);
        result_path_part = 0;
    }

    return result_path_part;
}


O3 struct path_part* pathparser_parse_path_part(struct path_part* last_part, const char** path)
{
    const char* path_part_str = pathparser_get_path_part(path);

    if (!path_part_str)
        return 0;

    struct path_part* part = kcalloc(sizeof(struct path_part));
    part->part = path_part_str;
    part->next = 0x00;

    if (last_part)
        last_part->next = part;
    
    return part;
}


O3 void pathparser_free(struct path_root* obj)
{
    struct path_part* pr = obj->first;
    struct path_part* tmp_pr;

    while (pr) {
        tmp_pr = pr->next;      // salvo il prossimo

        kfree((void*) pr->part);    // libero l'array di char
        kfree((void*) pr);

        pr = tmp_pr;            // ripristino il prossimo
    }

    kfree((void*) obj);
}


O3 struct path_root* pathparser_parse(const char* path, const char* current_dir)
{
    i32 res = 0;
    const char* tmp_path = path;
    struct path_root* path_root = 0;

    if (strlen(path) > KERNEL_FS_MAX_PATH)
        goto out;

    res = pathparser_get_drive_by_path(&tmp_path);
    if (res < 0)
        goto out;
    
    path_root = pathparser_create_root(res);

    if (!path_root)
        goto out;

    struct path_part* path_first = pathparser_parse_path_part(NULL, &tmp_path);

    if (!path_first)
        goto out;
    
    path_root->first = path_first;
    struct path_part* part = pathparser_parse_path_part(path_first, &tmp_path);

    while (part)
        part = pathparser_parse_path_part(part, &tmp_path);

    out:
        return path_root;
}