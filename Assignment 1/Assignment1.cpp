// Gianna Julio

#include <iostream>
using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
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
