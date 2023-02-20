// Gianna Julio

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// initialize array as global variable
string items[666];

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
            items[i] = item; // store item string
            i++; // increment counter
        }
        itemFile.close();
    }

    // confirm that all items have been successfully stored in the array
    // cout << items[665] << endl;
}

// node class
class Node
{
public:
    string value;
    Node* pointer;

    // default constructor
    Node()
    {
        value = "";
        pointer = NULL;
    }

    // overloaded constructor
    Node(string v)
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

    // default constructor
    SinglyLinkedList()
    {
        head = NULL;
        tail = NULL;
    }

    // add front
    void addFront(Node* n)
    {
        n->pointer = head;
        head = n;
    }

    // add end
    void addEnd(Node* n)
    {
        tail->pointer = n;
        n->pointer = NULL;
    }

    // remove
    void remove(int pos)
    {
        if (head == NULL)
        {
            cout << "Empty list" << endl;
            return;
        }

        // Check if the position is greater than length
        if (length() < pos)
        {
            cout << "Index out of range" << endl;
            return;
        }

        // Declare temp1
        Node* temp1 = head, * temp2 = NULL;

        // Traverse the list to find the node to be deleted.
        while (pos-- > 1)
        {
            // Update temp2
            temp2 = temp1;

            // Update temp1
            temp1 = temp1->pointer;
        }

        // Change the pointer of previous node
        temp2->pointer = temp1->pointer;

        // Delete the node
        delete temp1;
    }

    // remove front
    void removeFront()
    {
        Node* temp = head;
        // Update head
        head = head->pointer;
        delete temp;
        return;
    }

    // remove end
    void removeEnd()
    {
        Node* temp = head, * prev = NULL;
        while (temp->pointer != NULL)
        {
            prev = temp;
            temp = temp->pointer;
        }
        delete temp;
        prev->pointer = NULL;
        tail = prev;
        return;
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
            cout << temp->value << endl;
            temp = temp->pointer;
        }

    }

    // return length for easy access - traverse list with counter
    int length()
    {
        // start at head with length 0
        Node* temp = head;
        int len = 0;

        // if list is empty
        if (head == NULL)
        {
            return 0;
        }

        // traverse and increment
        while (temp != NULL)
        {
            len++;
            temp = temp->pointer;
        }

        return len;
    }
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
    
    // ignore spaces, caps, punctuation

    cout << items[0] << endl;
    return 0;
}
