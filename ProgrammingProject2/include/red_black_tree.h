#ifndef RED_BLACK_TREE_H
 #define RED_BLACK_TREE_H

#define RED true
#define BLACK false
#define NIL_KEY -1

#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>

typedef struct node
{
    int key;
    struct node * left;
    struct node * right;
    struct node * parent;
    bool color;
} node_t;

typedef struct tree
{
    node_t * root;
} tree_t;

void insert_to_tree(tree_t * tree, node_t * in);
void delete_from_tree(tree_t * tree, node_t * out);
node_t * search_tree(tree_t * tree, node_t * find);
void balance_tree(tree_t * tree);
void left_rotate(tree_t * tree, node_t * n);
void right_rotate(tree_t * tree, node_t * n);

#endif