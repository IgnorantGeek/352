#ifndef RED_BLACK_TREE_H
 #define RED_BLACK_TREE_H

#define RED true
#define BLACK false
#define NIL_KEY -1

#include <pthread.h>
#include <iostream>
#include <fstream>

char const * DEFAULT_FILE_LOC = "/home/nick/Documents/Workspaces/352/ProgrammingProject2/inFile.txt"; // this is the default file location if you don't want to type in the file every time

class node
{
    protected:
        int key;
        bool color;
        node * left;
        node * right;
        node * parent;
    public:
        node();
        ~node();
        node(int key);
        node(int key, bool color);
        void set_left(node * _left);
        void set_right(node * _right);
        void set_parent(node * _parent);
        void set_color(bool _color);
        void set_children(node * _left, node * _right);
        void print();
        node * get_left() { return left; }
        node * get_right() { return right; }
        node * get_parent() { return parent; }
        int get_key() { return key; }
};

class tree
{
    public:
        node * root;
        node * location;
        tree();
        ~tree();
        void build_from_file(char const * fname, int search_threads, int modify_threads);
        void add_node(node * insert);
        void left_rotate(node * about);
        void right_rotate(node * about);
        void print_tree();
};

#endif