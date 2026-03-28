#ifndef PPARSER_H
#define PPARSER_H

#include "config.h"


struct path_part{
    const char* part;
    struct path_part* next;
};


struct path_root {
    i32 drive_no;
    struct path_part* first;
};


extern struct path_root* pathparser_parse(const char* path, const char* current_dir);
extern void pathparser_free(struct path_root* obj);

struct path_root* pathparser_parse(const char* path, const char* current_dir);
void pathparser_free(struct path_root* obj);

#endif