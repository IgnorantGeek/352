#ifndef RED_BLACK_TREE_H
 #define RED_BLACK_TREE_H

#define RED true
#define BLACK false

#include <pthread.h>
#include <iostream>
#include <fstream>
#include <mutex>

typedef struct node
{
    int key;
    node_t * left;
    node_t * right;
    bool color;
    std::mutex m;
} node_t;

typedef struct tree
{
    node_t * root;
    std::mutex m; // not sure if I need this
} tree_t;

void insert_to_tree(tree_t * tree, node_t * in);
void delete_from_tree(tree_t * tree, node_t * del);

#endif