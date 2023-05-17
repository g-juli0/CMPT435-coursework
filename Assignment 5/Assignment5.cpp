// Gianna Julio

#include <iostream>
#include <vector>

using namespace std;

// node for the directed graph
class Node
{
public:
    int id; // vector number
    vector<pair<Node*, int>> neighbors; // list of neighbors

    // add a neighbor
    void addNeighbor(Node* neighbor, int cost)
    {
        neighbors.push_back(make_pair(neighbor, cost));
    }

};

// directed graph class
class DirectedGraph
{
public:
    // store all nodes in the graph
    vector<Node*> nodes;  

    // add a node to the graph
    void addNode(Node* node)
    {
        nodes.push_back(node);
    }

    // display the directed graph
    void printGraph()
    {
        for (Node* node : nodes)
        {
            cout << "Node " << node->id << " is connected to: ";
            for (pair<Node*, int> neighbor : node->neighbors)
            {
                //             id of neighbor,               cost of neighbor
                cout << "(" << neighbor.first->id << ", " << neighbor.second << ") ";
            }
            cout << endl; // next line
        }
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
