#include <iostream>
#include <cuda.h>

using namespace std;

__global__ void vectorAdd(int *a, int *b, int *res, int size) {
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index < n) {
        res[index] = a[index] + b[index];
    }
}

int main() {
    int size = 10;
    
    int *arr1_cpu = new int[size];
    int *arr2_cpu = new int[size];
    int *res_cpu = new int[size];

    for(int i=0; i<size; i++) {
        arr1_cpu[i] = rand() % 100;
        arr2_cpu[i] = rand() % 100;
    }

    int *arr1_gpu, *arr2_gpu, *res_gpu;
    cudaMalloc(&arr1_gpu, size * sizeof(int));
    cudaMalloc(&arr2_gpu, size * sizeof(int));
    cudaMalloc(&res_gpu, size * sizeof(int));

    // copy vectors from cpu to gpu
    cudaMemcpy(arr1_gpu, arr1_cpu, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(arr2_gpu, arr2_cpu, size * sizeof(int), cudaMemcpyToHostDevice);

    // vector addition on GPU
    int block_size = 256;
    int grid_size = (size + block_size - 1) / block_size;

    vectorAdd<<<grid_size, block_size>>>(arr1_gpu, arr2_gpu, res_gpu, size);

    // copy res to cpu
    cudeMemcpy(res_cpu, res_gpu, size * sizeof(int), cudaMemcpyDeviceToHost);

    cout << "GPU Result : \n";
    for(int i=0; i<size; i++) cout << res_cpu[i] << " ";

    // vector add on cpu
    for(int i=0; i<size; i++) {
        res_cpu[i] = arr1_cpu[i] + arr2_cpu[i];
    }

    cout << "CPU Result : \n";
    for(int i=0; i<size; i++) cout << res_cpu[i] << " ";

    cudaFree(arr1_gpu);
    cudaFree(arr2_gpu);
    cudaFree(res_gpu);

    delete[] arr1_cpu;
    delete[] arr2_cpu;
    delete[] res_cpu;

}