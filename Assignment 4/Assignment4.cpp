// Gianna Julio

#include <iostream>         // file reading
#include <fstream>          // file reading
#include <string>           // strings
#include <algorithm>        // transform entire strings to lowercase for sorting

using namespace std;

// initialize array as global variable
string items[666];

// initialize matrix, adjacency list, and linked object class
const int MAX_N = 75;

// matrix class
class Matrix
{
public:
    int matrix[MAX_N][MAX_N] = {};
    int size; // actual size and number of vertices

    void addEdge(int v1, int v2)
    {
        matrix[v1][v2]++;
    }

    void print()
    {
        // print heading
        std::cout << "  |";
        for (int i = 1; i <= size; i++)
        {
            std::cout << " " << i;
        }
        std::cout << "\n"; // new line

        // print contents of matrix
        for (int i = 1; i <= size; i++)
        {
            std::cout << i << " |";
            for (int j = 1; j <= size; j++)
            {
                std::cout << " " << matrix[i-1][j-1];
            }
            std::cout << "\n"; // new line
        }
    }
};

// adjacency list class
class AdjacencyList
{
public:
    int adjacencyList[MAX_N][MAX_N] = {};
    int size; // actual size and number of vertices

    void addEdge(int v1, int v2)
    {
        // for each vector connected to v1
        for (int v : adjacencyList[v1])
        {
            // find the next empty space
            if (v == 0)
            {
                // assign new edge connection
                v = v2;
                break;
            }
        }
    }

    void print()
    {
        for (int i = 1; i <= size; i++)
        {
            std::cout << i << " : ";

            for (int j = 0; j < size; j++)
            {
                if (adjacencyList[i - 1][j] != 0)
                {
                    std::cout << adjacencyList[i - 1][j] << ", ";
                }
                else
                {
                    break;
                }
            }
            std::cout << "\n"; // new line
        }
    }
};

// node class for linked objects
class Node
{
public:
    int val;
    Node* pointer;
};

void loadGraphs()
{
    // initialize file
    fstream itemFile;
    itemFile.open("graphs1.txt", ios_base::in);

    if (itemFile.is_open())
    {
        // counter
        int i = 0;

        // initialize objects
        Matrix m;
        AdjacencyList adj;
        int n = 0; // size

        // while file still has items to read
        while (itemFile.good())
        {
            string line; // initialize item string
            getline(itemFile, line); // get line

            if (line.find("--") != std::string::npos)
            {
                // ignore this line
                std::cout << "ignore\n";
            }

            else if (line.find("graph") != std::string::npos)
            {
                m.print();      // print old matrix
                adj.print();    // print old adjacency list
                n = 0;          // reset size
            }

            else if (line.find("vertex") != std::string::npos)
            {
                // adjust sizing for each new vertex
                n++;
                m.size = n;
                adj.size = n;
                std::cout << "vertex" << n << "\n";
            }

            else if (line.find("edge") != std::string::npos)
            {
                // find v1 and v2
                int v1 = 0;
                int v2 = 0;
                m.addEdge(v1, v2);
                adj.addEdge(v1, v2);
                std::cout << "edge\n";
            }

            i++; // increment counter
        }
        itemFile.close();
    }
}

// load magic items into array from file
void loadItems()
{
    // initialize file
    fstream itemFile;
    itemFile.open("magicitems.txt", ios_base::in);

    if (itemFile.is_open())
    {
        // counter
        int i = 0;

        // while file still has items to read
        while (itemFile.good())
        {
            string item; // initialize item string
            getline(itemFile, item); // get line
            transform(item.begin(), item.end(), item.begin(), ::tolower); // transform whole string to lowercase
            items[i] = item; // store item string
            i++; // increment counter
        }
        itemFile.close();
    }
}

//BST
// definition of the AVL tree node
struct AVLNode {
    string data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

// function to get the height of a node
int height(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

// function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// function to create a new node with a given data
AVLNode* newNode(string data) {
    AVLNode* node = new AVLNode();
    node->data = data;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

// function to perform a right rotation on a node
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return the new root
    return x;
}

// function to perform a left rotation on a node
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return the new root
    return y;
}

// function to get the balance factor of a node
int getBalance(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// function to insert a new node into the tree
AVLNode* insertNode(AVLNode* node, string data) {
    // Perform the normal BST insertion
    if (node == nullptr) {
        return newNode(data);
    }

    if (data < node->data) {
        node->left = insertNode(node->left, data);
    }
    else if (data > node->data) {
        node->right = insertNode(node->right, data);
    }
    else {
        // Duplicate keys are not allowed
        return node;
    }

    // Update the height of the ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of the ancestor node
    int balance = getBalance(node);

    // If the node is unbalanced, then there are 4 possible cases

    // Left Left Case
    if (balance > 1 && data < node->left->data) {
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && data > node->right->data) {
        return leftRotate(node);
    }

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// function to print the tree in order
void inorderTraversal(AVLNode* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }
}

int main()
{
    // GRAPHS
    loadGraphs();

    // BST 
    loadItems();

    AVLNode* root = nullptr;

    for (string i : items)
    {
        root = insertNode(root, i);
    }
}
