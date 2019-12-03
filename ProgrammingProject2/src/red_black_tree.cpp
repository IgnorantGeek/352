#include "../include/red_black_tree.h"

using namespace std;

int main()
{
    // if (argc != 0)
    // {
    //     // either error or prompt the user to enter a file
    //     char * in = argv[0];
    // }
    // tree_t bTree;
    // int search_threads;
    // int modify_threads;
    return 0;
}

bool build_from_file(tree_t* tree, char * fname)
{
    ifstream inFile;
    inFile.open(fname, ios::in);
    if (!inFile.is_open())
    {
        cout << "Could not find the file with name: " << fname << endl;
        cout << "Note, the full path of the file is required." << endl;
        return false;
    }
    string line;
    // going to have to change how I scan the file
    while (getline(inFile, line))
    {
        if (line.back() == 'b')
        {
            // black node
            node_t in;
            in.color = BLACK;
            string sub;
            for (size_t i = 0; i < line.length(); i++)
            {
                if (sub.at(i) != 'b') sub += line.at(i);
            }
            stringstream to_int(sub);
            int hold = 0;
            to_int >> hold;

            in.key = hold;
            insert_to_tree(tree, &in);
        }
        if (line.back() == 'r')
        {
            // red node
            node_t in;
            in.color = RED;
            string sub;
            for (size_t i = 0; i < line.length(); i++)
            {
                if (sub.at(i) != 'r') sub += line.at(i);
            }
            stringstream to_int(sub);
            int hold = 0;
            to_int >> hold;

            in.key = hold;
            insert_to_tree(tree, &in);
        }
        if (line.front() == 'f')
        {
            // leaf node
            node_t in;
            in.color = BLACK;
            in.key = -1; // leaf marker
            insert_to_tree(tree, &in);
        }
    }

    return true;
}

void insert_to_tree(tree_t * tree, node_t* in)
{
    node_t * scan = tree->root;
    while (scan != nullptr)
    {
        if (in->key > scan->key) scan = scan->right;
        else scan = scan->left;
    }
    scan = in;
}

void remove_from_tree(tree_t * tree, node_t * out)
{
    node_t * scan = tree->root;
    while (scan != nullptr)
    {
        if (scan->key == out->key)
        {
            // remove scan
        }
        if (out->key > scan->key) scan = scan->right;
        if (out->key < scan->key) scan = scan->left;
    }
}

node_t * search_tree(tree_t * tree, node_t * find)
{
    node_t * scan = tree->root;
    while (scan != nullptr)
    {
        if (find->key == scan->key) return scan;
        if (find->key > scan->key) scan = scan->right;
        if (find->key < scan->key) scan = scan->left;
    }
    return nullptr;
}

// void balance_tree(tree_t * tree)
// {

// }

// void print_tree(tree_t * tree)
// {

// }

void left_rotate(tree_t * tree, node_t * n)
{
    node_t * y = n->right;
    n->right = y->left;
    if (y->left != nullptr) y->left->parent = n;
    y->parent = n->parent;
    if (n->parent == nullptr) tree->root = y;
    else if (n == n->parent->left) n->parent->left = y;
    else n->parent->right = y;
    y->left = n;
    n->parent = y;
}

void print_node(node_t * node)
{
    cout << node->key << endl;
    cout << node->color << endl;
    cout << "Left : " << node->left->key << " || Right : " << node->right->key << "\n" << endl;
}