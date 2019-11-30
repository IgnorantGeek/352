#include "../include/red_black_tree.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 0)
    {
        // either error or prompt the user to enter a file
    }
    tree_t bTree;
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
    while (getline(inFile, line))
    {
        if (line.back() == 'b')
        {
            // black node
        }
        if (line.back() == 'r')
        {
            // red node
        }
        if (line.front() == 'f')
        {
            // leaf node
        }
    }

    return true;
}

void insert_to_tree(tree_t * tree, node_t* in)
{
    node_t * scan = tree->root; // start at the root node
    while (scan != nullptr)
    {
        if (in->key > scan->key) scan = scan->right;
        else scan = scan->left;
    }
    scan = in;
}