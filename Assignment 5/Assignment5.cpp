// Gianna Julio

#include <iostream>
#include <vector>
#include <algorithm>

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

// item for knapsack problem
class Item
{
public:
    string name;
    double totalPrice;
    int qty;

    Item(string n, double p, int q)
    {
        name = n;
        totalPrice = p;
        qty = q;
    }
};

// function to compute best case in fractional knapsack problem
double fractionalKnapsack(int capacity, Item* items[]) {

    double totalValue = 0.0;

    for (int i = 0; i < 4; i++)
    {
        // if the whole item fits in the bag
        if (capacity >= items[i]->qty) {
            totalValue += items[i]->totalPrice;
            capacity -= items[i]->qty;
            // add it to the bag and decrease bag quantity
        }
        // take all that fits in the bag
        else {
            double fraction = (double)capacity / items[i]->qty;
            totalValue += fraction * items[i]->totalPrice;
            break;
        }
    }

    return totalValue;
}


int main()
{

    // fractional backpack problem
    Item* red       = new Item("red", 4.0, 4);      // unit value: 1
    Item* green     = new Item("green", 12.0, 6);   // unit value: 2
    Item* blue      = new Item("blue", 40.0, 8);    // unit value: 5
    Item* orange    = new Item("orange", 18.0, 2);  // unit value: 9

    Item* items[] = {orange, blue, green, red};

    cout << "Knapsack with capacity 1 has a value of " << fractionalKnapsack(1, items) << endl;
    cout << "Knapsack with capacity 6 has a value of " << fractionalKnapsack(6, items) << endl;
    cout << "Knapsack with capacity 10 has a value of " << fractionalKnapsack(10, items) << endl;
    cout << "Knapsack with capacity 20 has a value of " << fractionalKnapsack(20, items) << endl;
    cout << "Knapsack with capacity 21 has a value of " << fractionalKnapsack(21, items) << endl;
}
