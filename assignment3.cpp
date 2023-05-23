#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>
// #include <bits/stdc++.h>

using namespace std;

int main()
{
    vector<int> numbers = {10, 5, 7, 15, 3, 9, 12, 8};

    // Serial Operations
    int min_val_serial = numbers[0];
    int max_val_serial = numbers[0];
    int sum_serial = 0;

    double start_time_serial = omp_get_wtime();

    // Calculate min, max, sum and average serially
    for (int i = 0; i < numbers.size(); i++)
    {
        min_val_serial = min(min_val_serial, numbers[i]);
        max_val_serial = max(max_val_serial, numbers[i]);
        sum_serial += numbers[i];
    }

    double average_serial = static_cast<double>(sum_serial) / numbers.size();

    double end_time_serial = omp_get_wtime();

    // Printing results
    cout << "Serial Results:" << endl;
    cout << "Minimum value: " << min_val_serial << endl;
    cout << "Maximum value: " << max_val_serial << endl;
    cout << "Sum: " << sum_serial << endl;
    cout << "Average: " << average_serial << endl;
    cout << "Start time serial: " << start_time_serial << endl;
    cout << "End time serial: " << end_time_serial << endl;
    cout << "Time taken for serial operations: " << (end_time_serial - start_time_serial) << " seconds" << endl;

    // Parallel Operations
    int min_val_parallel = numbers[0];
    int max_val_parallel = numbers[0];
    int sum_parallel = 0;

    double start_time_parallel = omp_get_wtime();

    // The below command is changed due to prettier formatting, which is why I have added this same line in comment below without any formatting
    // #pragma omp parallel for reduction(min: min_val_parallel) reduction(max: max_val_parallel) reduction(+: sum_parallel)

#pragma omp parallel for reduction(min : min_val_parallel) reduction(max : max_val_parallel) reduction(+ : sum_parallel)

    for (int i = 0; i < numbers.size(); i++)
    {
        min_val_parallel = min(min_val_parallel, numbers[i]);
        max_val_parallel = max(max_val_parallel, numbers[i]);
        sum_parallel += numbers[i];
    }

    double average_parallel = static_cast<double>(sum_parallel) / numbers.size();

    double end_time_parallel = omp_get_wtime();

    cout << "\nParallel Results:" << endl;
    cout << "Minimum value: " << min_val_parallel << endl;
    cout << "Maximum value: " << max_val_parallel << endl;
    cout << "Sum: " << sum_parallel << endl;
    cout << "Average: " << average_parallel << endl;
    cout << "Start time parallel: " << start_time_parallel << endl;
    cout << "End time parallel: " << end_time_parallel << endl;
    cout << "Time taken for serial operations: " << (end_time_parallel - start_time_parallel) << " seconds" << endl;

    return 0;
}

// #include <iostream>
// #include <vector>
// #include <omp.h>
// #include <chrono>

// int main()
// {
//     vector<int> numbers = {10, 5, 7, 15, 3, 9, 12, 8};

//     // Serial Operations
//     int min_val_serial = numbers[0];
//     int max_val_serial = numbers[0];
//     int sum_serial = 0;

//     auto start_serial = chrono::high_resolution_clock::now();

//     for (int i = 0; i < numbers.size(); i++)
//     {
//         min_val_serial = min(min_val_serial, numbers[i]);
//         max_val_serial = max(max_val_serial, numbers[i]);
//         sum_serial += numbers[i];
//     }

//     double average_serial = static_cast<double>(sum_serial) / numbers.size();

//     auto end_serial = chrono::high_resolution_clock::now();
//     auto duration_serial = chrono::duration_cast<chrono::microseconds>(end_serial - start_serial);

//     cout << "Serial Results:" << endl;
//     cout << "Minimum value: " << min_val_serial << endl;
//     cout << "Maximum value: " << max_val_serial << endl;
//     cout << "Sum: " << sum_serial << endl;
//     cout << "Average: " << average_serial << endl;
//     cout << "Serial Execution Time: " << duration_serial.count() << " microseconds" << endl;

//     // Parallel Operations
//     int min_val_parallel = numbers[0];
//     int max_val_parallel = numbers[0];
//     int sum_parallel = 0;

//     auto start_parallel = chrono::high_resolution_clock::now();

// #pragma omp parallel for reduction(min : min_val_parallel) reduction(max : max_val_parallel) reduction(+ : sum_parallel)
//     for (int i = 0; i < numbers.size(); i++)
//     {
//         min_val_parallel = min(min_val_parallel, numbers[i]);
//         max_val_parallel = max(max_val_parallel, numbers[i]);
//         sum_parallel += numbers[i];
//     }

//     double average_parallel = static_cast<double>(sum_parallel) / numbers.size();

//     auto end_parallel = chrono::high_resolution_clock::now();
//     auto duration_parallel = chrono::duration_cast<chrono::microseconds>(end_parallel - start_parallel);

//     cout << "\nParallel Results:" << endl;
//     cout << "Minimum value: " << min_val_parallel << endl;
//     cout << "Maximum value: " << max_val_parallel << endl;
//     cout << "Sum: " << sum_parallel << endl;
//     cout << "Average: " << average_parallel << endl;
//     cout << "Parallel Execution Time: " << duration_parallel.count() << " microseconds" << endl;

//     return 0;
// }
