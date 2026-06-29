
#include "utilities/patricia_tree/patricia_tree.h"


MODULE_LICENSE("GPL-3.0");
MODULE_AUTHOR("naga272");
MODULE_DESCRIPTION("logica algoritmo patricia tree");


/*
* Patricia Tree algoritmo be like:
*
*  ├── CLS
   │
   ├── RE
   │    ├── BOOT
   │    └── LOAD_TIME
   │
   ├── QUIT
   │
   └── IFCONFIG
* */


patricia_node_t* command_tree;


command_func_t patricia_search(patricia_node_t* root, char* command)
{
    patricia_node_t* node = root;

    while (*command) {
        i32 found = 0;

        for (size_t i = 0; i < node->n_children; i++) {
            patricia_node_t* child = node->children[i];

            if (starts_with(command, child->key)) {
                command += child->key_len;
                node = child;
                found = 1;
                break;
            }
        }

        if (!found)
            return NULL;
    }

    return node->function;
}


patricia_node_t* create_node(char* key)
{
    patricia_node_t* node;

    node = kmalloc(sizeof(patricia_node_t));

    node->key_len = strlen(key);

    node->key = kmalloc(node->key_len + 1);

    memcpy(
        node->key,
        key,
        node->key_len + 1
    );

    node->function = NULL;

    node->children = NULL;
    node->n_children = 0;


    return node;
}


void add_child(patricia_node_t* parent, patricia_node_t* child)
{
    parent->children = krealloc(
        parent->children,
        sizeof(patricia_node_t*) * (parent->n_children),
        sizeof(patricia_node_t*) * (parent->n_children + 1)
    );

    if (!parent->children)
        kprintf("warning, error krealloc, parent->children is NULL");

    parent->children[parent->n_children] = child;

    parent->n_children++;
}


void patricia_split(patricia_node_t* parent, patricia_node_t* node, size_t index)
{

    patricia_node_t* old_child;

    char* suffix = node->key + index;
    old_child = create_node(suffix);

    old_child->function = node->function;

    old_child->children = node->children;

    old_child->n_children = node->n_children;

    /*
       trasformo il vecchio nodo
       
       REBOOT

       in

       RE
    */

    node->key[index] = '\0';
    node->key_len = index;

    node->function = NULL;

    node->children = NULL;

    node->n_children = 0;

    add_child(node, old_child);
}


void patricia_insert(patricia_node_t* root, char* command, command_func_t func)
{
    patricia_node_t* node = root;

    while (*command) {
        i32 found = 0;

        for (size_t i = 0; i < node->n_children; i++) {
            patricia_node_t* child = node->children[i];

            size_t common = common_prefix(command, child->key);

            if (common) {
                found = 1;

                /*
                 * caso:
                 *
                 * command:
                 * RELOAD
                 *
                 * child:
                 * RELOAD_TIME
                 *
                 */

                if (common < child->key_len) {
                    patricia_split(node, child, common);
                    child = node->children[i];
                }

                command += common;
                node = child;
                break;
            }
        }

        if (!found) {
            patricia_node_t* new = create_node(command);

            new->function = func;

            add_child(node,new);

            return;
        }
    }
    node->function = func;
}
