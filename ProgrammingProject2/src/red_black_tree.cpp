#include "../include/red_black_tree.h"

using namespace std;



void node::set_children(node * _left, node * _right)
{
    this->left = _left;
    this->right = _right;
}

void node::set_color(bool _color)
{
    this->color = _color;
}

void node::set_left(node * _left)
{
    this->left = _left;
}

void node::set_right(node * _right)
{
    this->right = _right;
}

node::node()
{
    this->key = 0;
    this->color = false;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

node::node(int key)
{
    this->key = key;
    this->color = false;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
}

node::node(int key, node * _parent)
{
    this->key = key;
    this->color = false;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = _parent;
}

tree::tree()
{
    this->root = nullptr;
    this->location = root;
}

tree::~tree()
{
    // delete all the nodes underneath root, then delete root
}
/**
 * Function that initializes the binary tree and builds the structure from a file
 * */
void tree::build_from_file(char const * fname,
                           int search_threads,
                           int modify_threads)
{
    ifstream inFile;
    inFile.open(fname, ios::in);
    if (!inFile.is_open())
    {
        cout << "Could not find the file with name: " << fname << endl;
        cout << "Note, the full path of the file is required." << endl;
        return;
    }
    string line;
    
    string tree_nodes;

    getline(inFile, tree_nodes);
    
    string hold_str = "";
    // for (size_t i = 0; i < tree_nodes.length(); i++)
    // {
    //     if (tree_nodes.at(i) == ',')
    //     {
    //         cout << "Hold node: " << hold_node.key << endl;
    //         add_child(tree, &hold_node);
    //         hold_str = "";
    //         hold_node = {
    //             0,
    //             nullptr,
    //             nullptr,
    //             nullptr,
    //             false,
    //         };
    //     }
    //     else if (tree_nodes.at(i) == 'b')
    //     {
    //         hold_node.key = stoi(hold_str);
    //         hold_node.color = BLACK;
            
    //     }
    //     else if (tree_nodes.at(i) == 'r')
    //     {
    //         // red node
    //         hold_node.color = RED;
    //         hold_node.key = stoi(hold_str);
    //     }
    //     else if (tree_nodes.at(i) == 'f')
    //     {
    //         // leaf node
    //         hold_node.color = BLACK;
    //         hold_node.key = NIL_KEY; // leaf marker
    //     }
    //     else
    //     {
    //         hold_str.push_back(tree_nodes.at(i));
    //     }
    //     if (i+1 == tree_nodes.length())
    //     {
    //         cout << "Hold node: " << hold_node.key << endl;
    //         add_child(tree, &hold_node);
    //         hold_str = "";
    //         hold_node = {
    //             0,
    //             nullptr,
    //             nullptr,
    //             nullptr,
    //             false,
    //         };
    //     }
    // }

    // // string hold = "";
    // // for (size_t i = 16; i < line.length(); i++)
    // // {
    // //     hold += line.at(i);
    // // }
    // // search_threads = stoi(hold);
    // // getline(inFile, line);
    // // hold = "";
    // // for (size_t i = 16; i < line.length(); i++)
    // // {
    // //     hold += line.at(i);
    // // }
    // // modify_threads = stoi(hold);
    // return true;
}

/**
 * Method to insert a new node into the tree
 */
void tree::add_node(node * insert)
{
    // we will assume that location is always at the correct spot in the tree
    if (this->location->left() == nullptr) 
    {
        insert->parent = this->location;
        this->location->set_left(insert);
    }
}

// void balance_tree(tree_t * tree)
// {

// }

/** 
 * Performs a left rotate at a given node in the tree
 */
// void tree::left_rotate(node_t * n)
// {
//     node_t * y = n->right;
//     n->right = y->left;
//     if (y->left != nullptr) y->left->parent = n;
//     y->parent = n->parent;
//     if (n->parent == nullptr) tree->root = y;
//     else if (n == n->parent->left) n->parent->left = y;
//     else n->parent->right = y;
//     y->left = n;
//     n->parent = y;
// }

/** 
 * Prints a given node
 */
void node::print()
{
    cout << this->key << endl;
    cout << this->color << endl;
}

/**
 * Main entry point of the application
 * */
int main()
{
    char const * fname = DEFAULT_FILE_LOC;
    int searchThreads = 0;
    int modifyThreads = 0;
    tree * BinaryTree = new tree();

    // build from file here
    

    delete BinaryTree;
    return 0;
}