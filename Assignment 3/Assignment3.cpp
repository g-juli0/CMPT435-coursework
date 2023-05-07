// Gianna Julio

#include <iostream>         // file reading
#include <fstream>          // file reading
#include <iomanip>          // output formatting
#include <stdio.h>          // output formatting
#include <string>           // strings
#include <algorithm>        // transform entire strings to lowercase for sorting

using namespace std;

// node class
class HashNode
{
public:
    string item;
    HashNode* pointer;

    // default constructor initializes item as empty string and pointer as null
    HashNode()
    {
        item = "";
        pointer = nullptr;
    }

    // constructor that takes a specific item string as input
    HashNode(string i)
    {
        item = i;
        pointer = nullptr;
    }
};

// hash table class
class HashTable {
private:
    // set size
    static const int tableSize = 250;

    // array of pointers to nodes
    HashNode* table[tableSize];

public:

    HashTable()
    {
        HashNode* table[tableSize];

        for (int i = 0; i < tableSize; i++)
        {
            table[i] = new HashNode();
        }
    }

    // hash function for strings
    int hash(string target)
    {
        int hash = 0;
        for (char c : target)
        {
            hash += c;
        }
        return hash % tableSize;
    }

    // insert node into hash table
    void insert(string item)
    {
        HashNode* newNode = new HashNode(item);
        int index = hash(item);

        if (table[index] == nullptr)
        {
            table[index] = newNode;
        }
        //table[index] = newNode;

        /*
        if (table[index] == nullptr)
        {
            table[index] = newNode;
        }
        else {
            HashNode* temp = table[index];
            while (temp->pointer != nullptr)
            {
                temp = temp->pointer;
            }
            temp->pointer = newNode;
        }
        */
    }

    // look up target in hash table
    int lookup(string target)
    {
        int index = hash(target);
        int comparisons = 0;

        HashNode* temp = table[index];
        while (temp != nullptr)
        {
            comparisons++;
            if (temp->item == target)
            {
                return comparisons;
            }
            temp = temp->pointer;
        }
        return comparisons;
    }
};

// initialize array as global variable
string items[666];

// loadItems from last file
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

// sort items from last file (merge)
int merge(string arr[], int left, int mid, int right)
{
    // initialize comparision counter
    int comparisons = 0;

    // find size of two subarrays
    int arrayOne = mid - left + 1;
    int arrayTwo = right - mid;

    // create temp arrays
    auto* leftArray = new string[arrayOne];
    auto* rightArray = new string[arrayTwo];

    // copy data to temp arrays leftArray[] and rightArray[]
    for (int i = 0; i < arrayOne; i++)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < arrayTwo; j++)
        rightArray[j] = arr[mid + 1 + j];

    int indexOfArrayOne = 0; // initial index of first sub-array
    int indexOfArrayTwo = 0; // initial index of second sub-array
    int indexOfMergedArray = left; // initial index of merged array

    // merge temp arrays back into array
    while (indexOfArrayOne < arrayOne && indexOfArrayTwo < arrayTwo) {
        // if value in left array is smaller, left value goes into merged array next
        if (leftArray[indexOfArrayOne] <= rightArray[indexOfArrayTwo]) {
            arr[indexOfMergedArray] = leftArray[indexOfArrayOne];
            indexOfArrayOne++;
        }
        // if right is smaller, right vale goes into merged array next
        else {
            arr[indexOfMergedArray] = rightArray[indexOfArrayTwo];
            indexOfArrayTwo++;
        }
        // increment comparison counter and index of merged array
        comparisons++;
        indexOfMergedArray++;
    }

    // copy remaining elements of left[], if any
    while (indexOfArrayOne < arrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfArrayOne];
        indexOfArrayOne++;
        indexOfMergedArray++;
    }

    // copy remaining elements of right[], if any
    while (indexOfArrayTwo < arrayTwo) {
        arr[indexOfMergedArray] = rightArray[indexOfArrayTwo];
        indexOfArrayTwo++;
        indexOfMergedArray++;
    }

    // reallocate memory used for subarrays
    delete[] leftArray;
    delete[] rightArray;

    return comparisons;
}

// merge sort
int mergeSort(string arr[], int start, int end)
{
    // initialize comparison count
    int comparisons = 0;

    // base case
    if (start >= end)
        return comparisons;

    // find midpoint of array
    int mid = start + (end - start) / 2;

    // recursively sort both sides
    comparisons += mergeSort(arr, start, mid);
    comparisons += mergeSort(arr, mid + 1, end);

    // merge all subarrays back together after breaking out of recusion
    // and add comparisions to running total
    comparisons += merge(arr, start, mid, end);

    return comparisons;
}

// linear search
int linearSearch(string arr[], int size, string target) {
    int comparisons = 0;

    for (int i = 0; i < size; i++) {
        // increment comparions - checking each item in list
        comparisons++;
        if (arr[i] == target) {
            // if target is found, break out of function
            return comparisons;
        }
    }
    // if not found, return total compares
    return comparisons;
}

// binary search
int binarySearch(string arr[], int size, string target) {
    int comparisons = 0;
    int low = 0;
    int high = size - 1;

    while (low <= high) {
        comparisons++;
        int mid = (low + high) / 2;
        if (arr[mid] == target) {
            return comparisons;
        }
        else if (arr[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return comparisons;
}

// display formatted summary of sorts
void display(string searchType, double comparisons)
{
    // display heading - left justified, width of 34, filler char of '-', title, end line
    cout << left << setw(34) << setfill('-') << searchType + " " << endl;
    // display label left aligned in 25 spaces, followed by value right aligned (default) with 8 spaces
    printf("%-25s %8.3f\n", "Average comparisions:", comparisons);
    // extra spacing
    cout << endl;
}

int main()
{
    // load and sort items
    loadItems();
    mergeSort(items, 0, 666);

    // create and fill hash table
    HashTable h;
    for (string i : items)
    {
        h.insert(i);
    }

    // initialize random seed
    srand(time(NULL));

    // initial totals - used to compute averages later
    double totalComparesLinear = 0;
    double totalComparesBinary = 0;
    double totalComparesHashes = 0;

    // loops to pick a new random item, perform all searches, and compile results
    for (int i = 0; i < 42; i++)
    {
        // choose random item
        string randItem = items[rand() % 666];
        
        double linearComparisons = linearSearch(items, 666, randItem);
        totalComparesLinear += linearComparisons;
        //std::cout << linearComparisons << "\n";

        double binaryComparisons = binarySearch(items, 666, randItem);
        totalComparesBinary += binaryComparisons;
        //std::cout << binaryComparisons << "\n";

        double hashComparisons = h.lookup(randItem);
        totalComparesHashes += hashComparisons;
        //std::cout << hashComparisons << "\n";

    }

    // compute averages
    double avgComparesLinear = totalComparesLinear / 42.0;
    double avgComparesBinary = totalComparesBinary / 42.0;
    double avgComparesHashes = totalComparesHashes / 42.0;

    // display summary
    display("Linear Search", avgComparesLinear);
    display("Binary Search", avgComparesBinary);
    display("Hash Table with chaining", avgComparesHashes);

}
