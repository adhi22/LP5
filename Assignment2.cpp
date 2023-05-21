// // #include <iostream>
// // #include <ctime>
// // #include <cstdlib>
// // #include <omp.h>
#include <bits/stdc++.h>
using namespace std;

// Function to swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Sequential Bubble Sort
void sequentialBubbleSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int size)
{
    int i, j;
#pragma omp parallel shared(arr, size) private(i, j)
    {
        for (i = 0; i < size - 1; i++)
        {
#pragma omp for
            for (j = 0; j < size - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }
}

// Function to print an array
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    const int size = 10;
    int arr[size];

    // Fill the array with random numbers
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }

    // Sequential Bubble Sort
    cout << "Sequential Bubble Sort:" << endl;
    printArray(arr, size);

    clock_t start = clock();
    sequentialBubbleSort(arr, size);
    clock_t end = clock();
    double sequentialTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    printArray(arr, size);
    cout << "Time taken (sequential): " << sequentialTime << " seconds" << endl;

    // Fill the array with random numbers again
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;
    }

    // Parallel Bubble Sort
    cout << "\nParallel Bubble Sort:" << endl;
    printArray(arr, size);

    start = clock();
    parallelBubbleSort(arr, size);
    end = clock();
    double parallelTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    printArray(arr, size);
    cout << "Time taken (parallel): " << parallelTime << " seconds" << endl;

    return 0;
}

// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// #include <omp.h>

// // Sequential bubble sort
// void sequentialBubbleSort(int *arr, int size)
// {
//     for (int i = 0; i < size - 1; i++) {
//         for (int j = 0; j < size - i - 1; j++) {
//             if (arr[j] > arr[j + 1]) {
//                 // Swap elements
//                 int temp = arr[j];
//                 arr[j] = arr[j + 1];
//                 arr[j + 1] = temp;
//             }
//         }
//     }
// }

// // Parallel bubble sort
// void parallelBubbleSort(int *arr, int size)
// {
//     int i, j;

//     #pragma omp parallel shared(arr, size) private(i, j)
//     {
//         for (i = 0; i < size - 1; i++) {
//             #pragma omp for
//             for (j = 0; j < size - i - 1; j++) {
//                 if (arr[j] > arr[j + 1]) {
//                     // Swap elements
//                     int temp = arr[j];
//                     arr[j] = arr[j + 1];
//                     arr[j + 1] = temp;
//                 }
//             }
//         }
//     }
// }

// int main()
// {
//     const int size = 10000;
//     int arr[size];

//     // Initialize array with random values
//     std::srand(std::time(0));
//     for (int i = 0; i < size; i++) {
//         arr[i] = std::rand() % 1000;
//     }

//     // Perform sequential bubble sort
//     double startTime = omp_get_wtime();
//     sequentialBubbleSort(arr, size);
//     double endTime = omp_get_wtime();

//     std::cout << "Sequential Bubble Sort: " << (endTime - startTime) << " seconds" << std::endl;

//     // Re-initialize array with random values
//     for (int i = 0; i < size; i++) {
//         arr[i] = std::rand() % 1000;
//     }

//     // Perform parallel bubble sort
//     startTime = omp_get_wtime();
//     parallelBubbleSort(arr, size);
//     endTime = omp_get_wtime();

//     std::cout << "Parallel Bubble Sort: " << (endTime - startTime) << " seconds" << std::endl;

//     return 0;
// }
