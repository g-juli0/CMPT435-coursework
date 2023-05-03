// Gianna Julio

#include <iostream>         // file reading
#include <fstream>          // file reading
#include <iomanip>          // output formatting
#include <stdio.h>          // output formatting
#include <string>           // strings
#include <algorithm>        // transform entire strings to lowercase for sorting
using namespace std;

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
int linearSearch(string target)
{
    int comparisons = 0;

    return comparisons;
}

// binary search
int binarySearch(string target)
{
    int comparisons = 0;

    return comparisons;
}

// hash table with chaining

// display formatted summary of sorts
void display(string searchType, int comparisons, double time)
{
    // display heading - left justified, width of 34, filler char of '-', title, end line
    cout << left << setw(34) << setfill('-') << searchType + " " << endl;
    // display label left aligned in 25 spaces, followed by value right aligned (default) with 8 spaces
    printf("%-25s %8d\n", "Number of comparisions:", comparisons);
    // display label left aligned in 25 spaces, followed by value right aligned (default) with 5 spaces (8-3=5 characters for ' ms')
    printf("%-25s %5.f ms\n", "Elapsed time:", time);
    // extra spacing
    cout << endl;
}

int main()
{
    // load and sort items
    loadItems();
    mergeSort(items, 0, 666);

    // initialize random seed
    srand(time(NULL));

    // loops to pick a new random item, perform both searches, and compile results
    for (int i = 0; i < 42; i++)
    {
        // choose random item
        string randItem = items[rand() % 666];
        
        

    }

    std::cout << "Hello World!\n";
}
