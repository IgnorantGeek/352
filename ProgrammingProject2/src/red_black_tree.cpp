#include "../include/red_black_tree.h"

using namespace std;

class tree
{
    struct node
    {
        int data;
        node* left;
        node* right;
        node* parent;
        bool color;
    };

    int search_threads, modify_threads;
    node * root;
    node * location; // a pointer to the current location in the tree, for initialization

    public:
        tree()
        {
            root = NULL;
        }
        tree(char const * fname)
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
                    node * hold_node = new node();
                    hold_node -> color = hold_color;
                    hold_node -> data = hold_key;
                    this->insert_in_order(hold_node);
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
                    node * hold_node = new node();
                    hold_node -> color = hold_color;
                    hold_node -> data = hold_key;
                    this->insert_in_order(hold_node);
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
        ~tree()
        {
            root = clear(root);
        }
        node * findMin(node * t)
        {
            if(t == NULL) return NULL;
            else if(t->left == NULL) return t;
            else return findMin(t->left);
        }
        node * findMax(node * t)
        {
            if(t == NULL) return NULL;
            else if(t->right == NULL) return t;
            else return findMax(t->right);
        }
        node * clear(node* t)
        {
            if(t == NULL)
            return NULL;
            {
                clear(t->left);
                clear(t->right);
                delete t;
            }
            return NULL;
        }
        node * insert(int x, bool c, node* t)
        {
            if(t == NULL)
            {
                t = new node;
                t->data = x;
                t->color = c;
                t->left = t->right = NULL;
            }
            else if(x < t->data)
                t->left = insert(x, c, t->left);
            else if(x > t->data)
                t->right = insert(x, c, t->right);
            return t;
        }
        node * remove(int x, node* t)
        {
            node* temp;
            if(t == NULL) return NULL;
            else if(x < t->data) t->left = remove(x, t->left);
            else if(x > t->data) t->right = remove(x, t->right);
            else if(t->left && t->right)
            {
                temp = findMin(t->right);
                t->data = temp->data;
                t->right = remove(t->data, t->right);
            }
            else
            {
                temp = t;
                if(t->left == NULL)
                    t = t->right;
                else if(t->right == NULL)
                    t = t->left;
                delete temp;
            }

            return t;
        }
        void traverse(node* t)
        {
            if(t == NULL) return;
            cout << t->data << " ";
            traverse(t->left);
            traverse(t->right);
        }
        node * find(node *t, int x)
        {
            if(t == NULL) return NULL;
            else if(x < t->data) return find(t->left, x);
            else if(x > t->data) return find(t->right, x);
            else return t;
        }
        void insert_in_order(node* in)
        {
            // this is for the initial build
            if (root == NULL)
            {
                root = in;
                location = root;
                cout << "Root = " << root->data << endl;
            }
            else
            {
                cout << "Current location is at : " <<  location->data << endl;
                if (location->left == NULL)
                {
                    // insert this node on the left
                    cout << "Inserting node : " << in->data << " as left node of parent : " << location->data << endl;
                    in->parent = location;
                    location->left = in;
                }
                else
                {
                    // insert it on the right
                    cout << "Inserting node : " << in->data << " as right node of parent : " << location->data << endl;
                    in->parent = location;
                    location->right = in;
                }
                if (in->data == NIL_KEY)
                {
                    cout << "Begin parsing up" << endl;
                    node * scan = location;
                    while (scan->right != NULL)
                    {
                        scan = scan->parent;
                        if (scan == root && root->right != NULL) return;
                    }
                    location = scan;
                }
                else location = in;
                cout << "Location is now : " << location->data << endl;
            }
        }
        void print()
        {
            traverse(root);
            cout << endl;
        }
};

/**
 * Main entry point of the application
 * */
int main()
{
    char const * fname = DEFAULT_FILE_LOC;
    tree * BinaryTree = new tree(fname);

    BinaryTree->print();

    delete BinaryTree;
    return 0;
}