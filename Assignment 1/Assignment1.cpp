// Gianna Julio

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// load magic items into array from file
void loadItems()
{
    // initialize array
    string items[666];

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
            items[i] = item; // store item string
            i++; // increment counter
        }
        itemFile.close();
    }

    // confirm that all items have been successfully stored in the array
    cout << items[665] << endl;
}

// node class
class Node
{
public:
    int value;
    Node* pointer;

    // default constructor
    Node()
    {
        value = 0;
        pointer = NULL;
    }

    // overloaded constructor
    Node(int v)
    {
        value = v;
        pointer = NULL;
    }
};

// singly linked list
class SinglyLinkedList
{
public:
    Node* head;
    Node* tail;
    int length;

    // default constructor
    SinglyLinkedList()
    {
        head = NULL;
        tail = NULL;
        length = 0;
    }

    // insert
    void insert(int pos)
    {

    }
    // remove
    void remove(int pos)
    {

    }
    // print
    void print()
    {
        Node* temp = head;

        // if list is empty
        if (head == NULL)
        {
            cout << "Empty list" << endl;
            return;
        }

        while (temp != NULL)
        {
            cout << temp->pointer << endl;
            temp = temp->pointer;
        }

    }
    // get
    // set
};

// stack - first in, last out
class Stack
{
    // push
    // pop
};

// queue - first in, first out
class Queue
{
    // enqueue
    // dequeue
};

// MAIN FUNCTION ------------------------------------------------------------------------------
int main()
{
    loadItems();
    cout << "Hello World!" << endl;
    return 0;
}
