// Gianna Julio

#include <iostream>         // file reading
#include <fstream>          // file reading
#include <string>           // strings
#include <algorithm>        // transform entire strings to lowercase for sorting

using namespace std;

// initialize matrix, adjacency list, and linked object class
const int MAX_N = 75;

class Matrix
{
public:
    int matrix[MAX_N][MAX_N];
    int n; // actual size and number of vertices

    void addEdge(int v1, int v2)
    {
        matrix[v1][v2]++;
    }

    void print()
    {
        // print heading
        std::cout << "  | ";
        for (int i = 1; i <= n; i++)
        {
            std::cout << " " << i;
        }
        std::cout << "\n"; // new line

        // print contents of matrix
        for (int i = 1; i <= n; i++)
        {
            std::cout << i << " |";
            for (int j = 1; j <= n; j++)
            {
                std::cout << " " << matrix[i-1][j-1];
            }
            std::cout << "\n"; // new line
        }
    }
};

class AdjacencyList
{
public:
    int adjacencyList[MAX_N][MAX_N];
    int n; // actual size and number of vertices

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
        for (int i = 1; i <= n; i++)
        {
            std::cout << i << " | ";

            for (int j = 0; j < n; j++)
            {
                if (adjacencyList[i - 1][j] != 0)
                {
                    std::cout << adjacencyList[i - 1][j];
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

class Node
{
public:
    int val;
    Node* pointer;
};

void loadItems()
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
                //m.print();
                //adj.print();
                n = 0; // reset size
                std::cout << "new\n";
            }

            else if (line.find("vertex") != std::string::npos)
            {
                n++;
                std::cout << "vertex" << n << "\n";
            }

            else if (line.find("edge") != std::string::npos)
            {
                // find v1 and v2
                std::cout << "edge\n";
            }

            i++; // increment counter
        }
        itemFile.close();
    }
}

int main()
{
    loadItems();
    //std::cout << "Hello World!\n";
}
