#include "../include/red_black_tree.h"

using namespace std;

void node::set_children(node * _left, node * _right)
{
    left = _left;
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

void node::set_parent(node * _parent)
{
    this->parent = _parent;
}

void node::print()
{
    cout << this->key << endl;
    cout << this->color << endl;
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

node::node(int key, bool color)
{
    this->key = key;
    this->color = color;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
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
    int hold_key = 0;
    bool hold_color = BLACK;
    for (size_t i = 0; i < tree_nodes.length(); i++)
    {
        if (tree_nodes.at(i) == ',')
        {
            node * hold_node = new node(hold_key, hold_color);
            cout << "New node found: " << hold_node->get_key() << endl;
            this->add_node(hold_node);
            hold_key = 0;
            hold_color = BLACK;
            hold_str = "";
        }
        else if (tree_nodes.at(i) == 'b')
        {
            hold_key = stoi(hold_str);
            hold_color = BLACK;
            
        }
        else if (tree_nodes.at(i) == 'r')
        {
            // red node
            hold_color = RED;
            hold_key = stoi(hold_str);
        }
        else if (tree_nodes.at(i) == 'f')
        {
            // leaf node
            hold_color = BLACK;
            hold_key = NIL_KEY; // leaf marker
        }
        else
        {
            hold_str.push_back(tree_nodes.at(i));
        }
        if (i+1 == tree_nodes.length())
        {
            // The last element in the tree descriptors is always an f
            this->add_node(new node(-1, BLACK));
        }
    }

    // string hold = "";
    // for (size_t i = 16; i < line.length(); i++)
    // {
    //     hold += line.at(i);
    // }
    // search_threads = stoi(hold);
    // getline(inFile, line);
    // hold = "";
    // for (size_t i = 16; i < line.length(); i++)
    // {
    //     hold += line.at(i);
    // }
    // modify_threads = stoi(hold);
}

/**
 * Method to insert a new node into the tree
 */
void tree::add_node(node * insert)
{
    if (this->root == nullptr) 
    {
        root = insert;
        location = root;
        return;
    }
    if (this->location->get_left() == nullptr) 
    {
        insert->set_parent(this->location);
        this->location->set_left(insert);
        this->location = insert;
    }
    else if (this->location->get_right() == nullptr)
    {
        insert->set_parent(this->location);
        this->location->set_right(insert);
        this->location = insert;
    }
    else throw "Bad news";
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
 * Main entry point of the application
 * */
int main()
{
    char const * fname = DEFAULT_FILE_LOC;
    int searchThreads = 0;
    int modifyThreads = 0;
    tree * BinaryTree = new tree();

    // build from file here
    BinaryTree->build_from_file(fname, searchThreads, modifyThreads);


    delete BinaryTree;
    return 0;
}