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
    node_t hold_node = {
        0,
        nullptr,
        nullptr,
        nullptr,
        false,
    };
    node_t parent_node = {
        0,
        nullptr,
        nullptr,
        nullptr,
        false,
    };
    for (size_t i = 0; i < tree_nodes.length(); i++)
    {
        if (tree_nodes.at(i) == ',')
        {
            append_to_tree(tree, &parent_node, &hold_node);
            cout << "Hold node: " << hold_node.key << endl;
            if (hold_node.parent != nullptr) cout << "Parent node: " << hold_node.parent->key << "\n" << endl;
            if (hold_node.key == NIL_KEY)
            {
                while (true)
                {
                    hold_node = *hold_node.parent;
                    if (hold_node.right == nullptr)
                    {
                        parent_node = hold_node;
                        break;
                    }
                    else if (hold_node.left == nullptr) // REMOVE ME
                    {
                        cout << "We should never see this" << endl;
                        parent_node = hold_node;
                        break;
                    }
                }
            }
            else parent_node = hold_node;
            hold_str = "";
            hold_node = {
                0,
                nullptr,
                nullptr,
                nullptr,
                false,
            };
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
    append_to_tree(tree, &parent_node, &hold_node);
    getline(inFile, line);
    string hold = "";
    for (size_t i = 16; i < line.length(); i++)
    {
        hold += line.at(i);
    }
    search_threads = stoi(hold);
    getline(inFile, line);
    hold = "";
    for (size_t i = 16; i < line.length(); i++)
    {
        hold += line.at(i);
    }
    modify_threads = stoi(hold);
    return true;
}

/**
 * Method to insert a new node into the tree
 */
void insert_to_tree(tree_t * tree, node_t* in)
{
    if (tree->root == nullptr) 
    {
        tree->root = in;
        return;
    }
    else
    {
        node_t * scan = tree->root;
        while (scan != nullptr)
        {

        }
    }
    
}

/** 
 * Method for adding nodes to the tree when building from a file
 */
void append_to_tree(tree_t * tree, node_t * parent, node_t * child)
{
    if (tree->root == nullptr)
    {
        tree->root = child;
    }
    else
    {
        //cout << "Parent key: " << parent->key << endl;
        if (child ->key == NIL_KEY)
        {
            if (parent->left == nullptr) parent->left = child;
            else if (parent->right == nullptr) parent -> right = child;
            else throw "Huston we have a problem.";
            child->parent = parent;
        }
        else if (child->key < parent->key)
        {
            parent->left = child;
            child->parent = parent;
        }
        else
        {
            parent->right = child;
            child->parent = parent;
        }
    }
    cout << "Current Node: " << child->key << endl;
    if (child->parent != nullptr) cout << "Parent Node: " << child->parent->key << endl;
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
}

/**
 * Main entry point of the application
 * */
int main()
{
    char const * fname = DEFAULT_FILE_LOC;
    int searchThreads = 0;
    int modifyThreads = 0;
    tree_t bTree = {nullptr};
    if (!build_from_file(&bTree, fname, searchThreads, modifyThreads))
    {
        cout << "Error reading the input file. Exiting." << endl;
        return 1;
    }
    cout << bTree.root->key << endl;
    // rec_print_tree(&bTree, bTree.root);
    cout << searchThreads << " " << modifyThreads << endl;
    return 0;
}