// Gianna Julio

#include <iostream>     // file reading
#include <fstream>      // file reading
#include <string>       // strings
#include <time.h>       // random seed
#include <algorithm>    // transform whole strings to lowercase for comparisons
#include <stdio.h>      // print formatting
#include <ctime>        // measure elapsed time between sorts
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
            transform(item.begin(), item.end(), item.begin(), ::tolower); // transform whole string to lowercase
            items[i] = item; // store item string
            i++; // increment counter
        }
        itemFile.close();
    }
}

// swap
void swap(string* one, string* two)
{
    // store in temporary variable, then swap pointers
    string temp = *one;
    *one = *two;
    *two = temp;
}

// shuffle elements of the list
void shuffleList()
{
    // initialize random seed
    srand(time(NULL));

    for (int i = size(items)-1; i > 0; i--)
    {
        // choose random item
        int randIndex = rand() % i;

        // swap item at current pointer with random item
        swap(items[i], items[randIndex]);
    }
}

// selection sort
int selectionSort(string arr[], int n)
{
    // initialize comparison counter and minimum value index
    int comparisons = 0;
    int minIndex = 0;

    // first loop - loop through all of array
    for (int i = 0; i < n; i++)
    {
        // the minimum index of the unsorted portion of the array
        minIndex = i;

        // second loop - loop through the unsorted portion of the array (after i)
        for (int j = i+1; j <n; j++)
        {
            // if current value (at j) is less than the store minimum value
            if (arr[j] < arr[minIndex])
            {
                // save current (smaller) value's index as minimum index
                minIndex = j;
            }
            // increment comparision counter
            comparisons++;
        }

        // swap the smallest found element with the first element of the unsorted portion
        // if first element (at i) is not already the smallest
        if (minIndex != i)
        {
            swap(&arr[minIndex], &arr[i]);
        }
    }
    return comparisons;
}

// insertion sort
int insertionSort(string arr[], int n)
{
    int comparisions = 0;
    
    for (int i = 1; i < n; i++)
    {
        int j = i;

        while (j >= 0 && arr[j-1] > arr[j])
        {
            swap(arr[j], arr[j - 1]);
            j--;
            comparisions++;
        }
    }
    return comparisions;
}

// merge sort
// quick sort

void display(string sortType, int comparisons, double time)
{
    // display heading
    cout << sortType << " -------------------- " << endl;
    // display label left aligned in 25 spaces, followed by value right aligned (default) with 8 spaces
    printf("%-25s %8d\n", "Number of comparisions:", comparisons);
    // display label left aligned in 25 spaces, followed by value right aligned (default) with 5 spaces (8-3=5 characters for ' ms')
    printf("%-25s %5.f ms\n", "Elapsed time:", time);
    // extra spacing
    cout << endl;
}

// DELETE - for debugging
void simpleDisplay()
{
    for (string item : items)
    {
        cout << item << endl;
    }
}

int main()
{
    loadItems();

    // SELECTION SORT -----------------------------------------------------------------
    shuffleList(); // shuffle
    clock_t begin = clock(); // begin timer
    int selectionComparisons = selectionSort(items, 666); // call sort
    clock_t end = clock(); // end timer
    display("Selection Sort", selectionComparisons, end-begin); // display results

    // INSERTION SORT -----------------------------------------------------------------
    shuffleList(); // shuffle again
    begin = clock(); // restart timer
    int insertionComparisons = insertionSort(items, 666); // call sort
    end = clock(); // end timer
    display("Insertion Sort", insertionComparisons, end - begin); // display results
}
