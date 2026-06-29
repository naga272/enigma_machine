#ifndef PATRICIA_TREE_H
#define PATRICIA_TREE_H

#include "config.h"
#include "utilities/string/string.h"
#include "utilities/video/kprintf.h"

typedef u8 (*command_func_t)();


typedef struct patricia_node {
    char* key;                 // parte di stringa contenuta nel nodo
    size_t key_len;

    command_func_t function;   // NULL se non è un comando completo

    struct patricia_node** children;
    size_t n_children;

} patricia_node_t;


extern patricia_node_t* command_tree;
extern patricia_node_t* create_node(char* key);
extern void patricia_insert(patricia_node_t* root, char* command, command_func_t func);
extern command_func_t patricia_search(patricia_node_t* root, char* command);

#endif