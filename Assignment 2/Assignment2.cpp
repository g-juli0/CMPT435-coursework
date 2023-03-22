// Gianna Julio

#include <fstream>      // file reading
#include <iostream>     // file reading
#include <iomanip>      // output formatting
#include <stdio.h>      // output formatting
#include <string>       // strings
#include <time.h>       // used for random seed
#include <algorithm>    // transform whole strings to lowercase for comparisons
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

    // outer loop - iterate through each element
    for (int i = 0; i < n; i++)
    {
        // the minimum index of the unsorted portion of the array
        minIndex = i;

        // inner loop - loop through the unsorted portion of the array (after i)
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
    // initialize comparisions
    int comparisions = 0;
    
    // outer loop - iterate through each element
    for (int i = 1; i < n; i++)
    {
        // initialize second iterator at the beginning of the unsorted portion of the list (i)
        int j = i;

        // inner loop - iterate through sorted portion of the list, swapping elements until
        // the value is in the correct space and the previous element is smaller than the current
        while (j >= 0 && arr[j-1] > arr[j])
        {
            swap(arr[j], arr[j - 1]); // swap
            j--; // decrement
            comparisions++; // increment comparision counter
        }
    }
    return comparisions;
}

// merge arrays back together for mergeSort
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

    // merge  temp arrays back into array[left>right]
    while (indexOfArrayOne < arrayOne && indexOfArrayTwo < arrayTwo) {
        if (leftArray[indexOfArrayOne] <= rightArray[indexOfArrayTwo]) {
            arr[indexOfMergedArray] = leftArray[indexOfArrayOne];
            indexOfArrayOne++;
        }
        else {
            arr[indexOfMergedArray] = rightArray[indexOfArrayTwo];
            indexOfArrayTwo++;
        }
        comparisons++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of left[], if there are any
    while (indexOfArrayOne < arrayOne) {
        arr[indexOfMergedArray] = leftArray[indexOfArrayOne];
        indexOfArrayOne++;
        indexOfMergedArray++;
    }

    // Copy the remaining elements of right[], if there are any
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
    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);
    
    // merge all subarrays back together after breaking out of recusion
    // and add comparisions to running total
    comparisons += merge(arr, start, mid, end);

    return comparisons;
}

// quick sort
int quickSort(string arr[], int n)
{
    int comparisons = 0;



    return comparisons;
}

void display(string sortType, int comparisons, double time)
{
    // display heading - left justified, width of 34, filler char of '-', title, end line
    cout << left << setw(34) << setfill('-') << sortType + " " << endl;
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
    display("Insertion Sort", insertionComparisons, end-begin); // display results

    
    // MERGE SORT ---------------------------------------------------------------------
    shuffleList(); // shuffle again
    begin = clock(); // restart timer
    int mergeComparisions = mergeSort(items, 0, 666); // call sort;
    end = clock(); // end timer
    display("Merge Sort", mergeComparisions, end-begin); // display results

    // QUICK SORT ---------------------------------------------------------------------
    shuffleList(); // shuffle again
    begin = clock(); // restart timer
    int quickComparisions = quickSort(items, 666); // call sort
    end = clock(); // end timer
    display("Quick Sort", quickComparisions, end-begin); // display results
    
}
