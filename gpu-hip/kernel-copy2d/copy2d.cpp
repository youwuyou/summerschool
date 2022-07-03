#include <hip/hip_runtime.h>
#include <stdio.h>
#include <math.h>

// TODO: add a device kernel that copies all elements of a vector
//       using GPU threads in a 2D grid
__global__ void dcopy_(int m, int n, double* x, double* y){

   int row = blockIdx.x * blockDim.x + threadIdx.x;
   int col = blockIdx.y * blockDim.y + threadIdx.y;

   int stridex = gridDim.x * blockDim.x;
   int stridey = gridDim.y * blockDim.y;

    // copying using the indices
        for (; row < n; row += stridex){
            for(; col < m; col += stridey){
                    y[row * m + col] = x[row * m + col];
            }
        }
}




int main(void)
{
    int i, j;
    const int n = 600;
    const int m = 400;
    const int size = n * m;
    double x[size], y[size], y_ref[size];
    double *x_, *y_;

    // initialise data
    for (i=0; i < size; i++) {
        x[i] = (double) i / 1000.0;
        y[i] = 0.0;
    }
    // copy reference values (C ordered)
    for (i=0; i < n; i++) {
        for (j=0; j < m; j++) {
            y_ref[i * m + j] = x[i * m + j];
        }
    }

    // TODO: allocate vectors x_ and y_ on the GPU
    hipMalloc(&x_, sizeof(double) * size);
    hipMalloc(&y_, sizeof(double) * size);

    // TODO: copy initial values from CPU to GPU (x -> x_ and y -> y_)
    hipMemcpy(x_, x, sizeof(double) * size, hipMemcpyHostToDevice);
    hipMemcpy(y_, y, sizeof(double) * size, hipMemcpyHostToDevice);


    // TODO: define grid dimensions (use 2D grid!)
    //// dim3 blocks(600, 400);
    //// dim3 threads(256);

    dim3 blocks(10, 12);
    dim3 threads(64, 4);


    // TODO: launch the device kernel
    hipLaunchKernelGGL(dcopy_, blocks, threads, 0, 0, m, n, x_, y_);

    // TODO: copy results back to CPU (y_ -> y)
    hipMemcpy(y, y_, sizeof(double) * size, hipMemcpyDeviceToHost);

    // confirm that results are correct
    double error = 0.0;
    for (i=0; i < size; i++) {
        error += abs(y_ref[i] - y[i]);
    }
    printf("total error: %f\n", error);
    printf("  reference: %f at (42,42)\n", y_ref[42 * m + 42]);
    printf("     result: %f at (42,42)\n", y[42 * m + 42]);

    return 0;
}
