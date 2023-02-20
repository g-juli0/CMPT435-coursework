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
    char value;
    Node* pointer;

    // default constructor
    Node()
    {
        value = '\0';
        pointer = NULL;
    }

    // overloaded constructor
    Node(char v)
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
        // front is empty - first value
        if (head == NULL)
        {
            head = n;
            tail = n;
        }
        else
        {
            n->pointer = head;
            head = n;
        }
    }

    // add end
    void addEnd(Node* n)
    {
        // if no tail - either both head and tail are empty or just tail is null
        if (tail == NULL)
        {
            if (head == NULL)
            {
                addFront(n);
            }
            // just tail is null
            else
            {
                head->pointer = n;
                tail = n;
                n->pointer = NULL;
            }
        }
        else
        {
            tail->pointer = n;
            n->pointer = NULL;
            tail = n;
        }
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
class Stack: public SinglyLinkedList
{
public:
    Node* top;

    Stack()
    {
        top = NULL;
    }

    Stack(Node* n)
    {
        top = n;
    }

    // push - adds node to top of stack
    void push(Node* n)
    {
        addFront(n);
    }

    // pop - removes node from top of stack
    Node* pop()
    {
        return top;
        removeFront();
    }
};

// queue - first in, first out
class Queue: public SinglyLinkedList
{
public:
    Node* first;

    Queue()
    {
        first = NULL;
    }

    Queue(Node* n)
    {
        first = n;
    }

    // enqueue - adds node to end of queue
    void enqueue(Node* n)
    {
        addEnd(n);
    }

    // dequeue - removes node from front of queue
    Node* dequeue()
    {
        return first;
        removeFront();
    }
};

// MAIN FUNCTION ------------------------------------------------------------------------------
int main()
{
    loadItems();

    // for each string item in the list of magic items
    for (string item : items)
    {
        // initialize a Stack and Queue
        Stack s;
        Queue q;

        // for each character in the item name string
        for (char c : item)
        {
            // ignore spaces and punctuation
            if (isalpha(c))
            {
                // convert to lowercase to ignore capitalization
                char ch = tolower(c);

                // initialize character as a Node
                Node* chNode = new Node(ch);
                s.push(chNode);
                q.enqueue(chNode);
            }
        }


        bool palindrome = true;

        
        for (char c : item)
        {
            if (s.pop()->value != q.dequeue()->value)
                palindrome = false;
        }

        if (palindrome == true)
        {
            cout << item << endl;
        }
        
    }

    return 0;
}
