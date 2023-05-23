#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

// Sequential merge sort
void mergeSortSeq(vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    mergeSortSeq(left);
    mergeSortSeq(right);

    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < left.size())
        arr[k++] = left[i++];

    while (j < right.size())
        arr[k++] = right[j++];
}

// Parallel merge sort
void mergeSortParallel(vector<int> &arr)
{
    if (arr.size() <= 1)
        return;

    int mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

#pragma omp parallel sections
    {
#pragma omp section
        {
            mergeSortParallel(left);
        }

#pragma omp section
        {
            mergeSortParallel(right);
        }
    }

    int i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < left.size())
        arr[k++] = left[i++];

    while (j < right.size())
        arr[k++] = right[j++];
}

// Helper function to print the array
void printArray(const vector<int> &arr)
{
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main()
{
    vector<int> arr = {9, 3, 7, 1, 5, 10, 2, 8, 4, 6};

    cout << "Original array: ";
    printArray(arr);

    // Sequential merge sort
    vector<int> seqArr = arr;
    double seqStart = omp_get_wtime();
    mergeSortSeq(seqArr);
    double seqEnd = omp_get_wtime();
    cout << "\nSequential merge sort: ";
    printArray(seqArr);
    cout << seqStart << endl;
    cout << seqEnd << endl;
    cout << "Time taken for sequential merge sort: " << (seqEnd - seqStart) << " seconds\n";

    // Parallel merge sort
    vector<int> parallelArr = arr;
    double parallelStart = omp_get_wtime();
    mergeSortParallel(parallelArr);
    double parallelEnd = omp_get_wtime();
    cout << "\nParallel merge sort: ";
    printArray(parallelArr);
    cout << parallelStart << endl;
    cout << parallelEnd << endl;
    cout << "Time taken for parallel merge sort: " << (parallelEnd - parallelStart) << " seconds\n";

    return 0;
}

// command to run:
// g++ merge.cpp -lgomp -o merge
// ./merge