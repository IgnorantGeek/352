#include "../include/red_black_tree.h"

using namespace std;

/**
 * Function that initializes the binary tree and builds the structure from a file
 * */
bool build_from_file(tree_t* tree,
                     char const * fname,
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
    
    string tree_nodes;

    getline(inFile, tree_nodes);

    
    string hold_str = "";
    node_t hold_node;
    for (size_t i = 0; i < tree_nodes.length(); i++)
    {
        if (tree_nodes.at(i) == ',')
        {
            insert_to_tree(tree, &hold_node);
            hold_str = "";
            node_t reset;
            cout << "Resent num is : " << reset.key << endl;
            cout << "hold_node is currently : " << hold_node.key << "\nreseting hold node..." << endl;
            hold_node = reset;
            cout << "hold_node is now : " << hold_node.key << endl;
        }
        else if (tree_nodes.at(i) == 'b')
        {
            hold_node.key = stoi(hold_str);
            hold_node.color = BLACK;
            
        }
        else if (tree_nodes.at(i) == 'r')
        {
            // red node
            hold_node.color = RED;
            hold_node.key = stoi(hold_str);
        }
        else if (tree_nodes.at(i) == 'f')
        {
            // leaf node
            hold_node.color = BLACK;
            hold_node.key = NIL_KEY; // leaf marker
        }
        else
        {
            hold_str.push_back(tree_nodes.at(i));
        }
    }
    search_threads = 1;
    modify_threads = 1;
    cout << search_threads << " " << modify_threads << endl;
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

/**
 * Main entry point of the application
 * */
int main(int argc, char* argv[])
{
    char const * fname;
    int searchThreads = 0;
    int modifyThreads = 0;
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