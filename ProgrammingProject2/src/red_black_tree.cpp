#include "../include/red_black_tree.h"

using namespace std;

/**
 * Main entry point of the application
 * */
int main(int argc, char* argv[])
{
    char * fname = "";
    int searchThreads;
    int modifyThreads;
    if (argc == 0)
    {
        // either error or prompt the user to enter a file
        cout << "No input file detected. Using default file location at: " << DEFAULT_FILE_LOC << endl;
        fname = DEFAULT_FILE_LOC;
    }
    else fname = argv[0];
    tree_t bTree;
    if (!build_from_file(&bTree, fname, searchThreads, modifyThreads))
    {
        cout << "Error reading the input file. Exiting." << endl;
        return 1;
    }
    return 0;
}

/**
 * Function that initializes the binary tree and builds the structure from a file
 * */
bool build_from_file(tree_t* tree,
                     char * fname,
                     int search_threads,
                     int modify_threads)
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
    

    // FIX READING THE FILE
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
            in.key = NIL_KEY; // leaf marker
            insert_to_tree(tree, &in);
        }
    }

    return true;
}

/**
 * Method to insert a new node into the tree
 */
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

/** 
 * Method to remove a node from the tree
 */
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

/** 
 * Method to find a specified node in the tree
 */
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

/** 
 * Recursively prints all the nodes in the tree
 */
void rec_print_tree(tree_t * tree, node_t * curr)
{
    if (curr->key == NIL_KEY) print_node(curr);
    else 
    {
        print_node(curr);
        rec_print_tree(tree, curr->right);
        rec_print_tree(tree, curr->left);
    }
}

/** 
 * Performs a left rotate at a given node in the tree
 */
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

/** 
 * Prints a given node
 */
void print_node(node_t * node)
{
    cout << node->key << endl;
    cout << node->color << endl;
    cout << "Left : " << node->left->key << " || Right : " << node->right->key << "\n" << endl;
}