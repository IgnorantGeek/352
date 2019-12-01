#include "../include/red_black_tree.h"

using namespace std;

int main()
{
    // if (argc != 0)
    // {
    //     // either error or prompt the user to enter a file
    //     char * in = argv[0];
    // }
    tree_t bTree;
    int search_threads;
    int modify_threads;
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
    node_t * scan = tree->root; // start at the root node
    while (scan != nullptr)
    {
        if (in->key > scan->key) scan = scan->right;
        else scan = scan->left;
    }
    scan = in;
}

void print_tree(tree_t * tree)
{

}