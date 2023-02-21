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
}

// node class
class Node
{
public:
    char value;
    Node* pointer;
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
        head = nullptr;
        tail = nullptr;
    }

    // add front
    void addFront(char n)
    {
        // initialize character as a Node
        Node* chNode = new Node();
        chNode->value = n;
        //cout << n->value << endl;

        // front is empty - first value
        if (head == nullptr)
        {
            head = chNode;
            tail = chNode;
        }
        // otherwise, new node points to old node and replaces head
        else
        {
            chNode->pointer = head;
            head = chNode;
        }
    }

    // add end
    void addEnd(char n)
    {
        // initialize character as a Node
        Node* chNode = new Node();
        chNode->value = n;
        // if no tail - either both head and tail are empty or just tail is null
        if (tail == nullptr)
        {
            // if the list is empty, add as a head
            if (head == nullptr)
            {
                addFront(n);
            }
            // just tail is null
            else
            {
                head->pointer = chNode;
                tail = chNode;
                chNode->pointer = nullptr;
            }
        }
        // otherwise, tail pointer now points to new node and new node replaces tail
        else
        {
            tail->pointer = chNode;
            chNode->pointer = nullptr;
            tail = chNode;
        }
    }

    // remove front
    Node* removeFront()
    {
        Node* temp = head;
        // Update head
        head = head->pointer;
        // reallocate memory
        delete temp;
        return head;
    }

    // remove end
    Node* removeEnd()
    {
        // initialize temp and previous nodes
        Node* temp = head, * prev = nullptr;
        // while temp is not the tail
        while (temp->pointer != nullptr)
        {
            // save prev value
            prev = temp;
            // iterate through nodes
            temp = temp->pointer;
        }
        // reallocate memory
        delete temp;
        // set prev pointer to null and replace tail with prev
        prev->pointer = nullptr;
        tail = prev;
        return tail;
    }

    // print
    void print()
    {
        Node* temp = head;

        // if list is empty
        if (head == nullptr)
        {
            cout << "Empty list" << endl;
            return;
        }

        // iterate through nodes and print on same line, separated by spaces
        while (temp != nullptr)
        {
            cout << temp->value << " ";
            temp = temp->pointer;
        }
        // new line
        cout << endl;

    }

    // return length for easy access - traverse list with counter
    int length()
    {
        // start at head with length 0
        Node* temp = head;
        int len = 0;

        // traverse and increment
        while (temp != nullptr)
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
    // push - adds node to top of stack
    void push(char n)
    {
        addFront(n);
    }

    // pop - removes node from top of stack
    Node* pop()
    {
        return removeFront();
    }
};

// queue - first in, first out
class Queue: public SinglyLinkedList
{
public:
    // enqueue - adds node to end of queue
    void enqueue(char n)
    {
        addEnd(n);
    }

    // dequeue - removes node from front of queue
    Node* dequeue()
    {
        return removeFront();
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

                s.push(ch);
                q.enqueue(ch);
            }
        }

        // assume each item is a palindrome
        bool palindrome = true;

        // while stack (and queue - same length) is not empty
        while (s.length() > 1)
        {
            // grab each head value
            char stackChar = s.pop()->value;
            char queueChar = q.dequeue()->value;

            // compare - if there are any that dont match the word is not a palindrome
            if (stackChar != queueChar)
                palindrome = false;
        }

        // if the bool is still true after the loop, all letters matched
        if (palindrome == true)
        {
            // print out the palindrome item
            cout << item << endl;
        }
    }
    return 0;
}
