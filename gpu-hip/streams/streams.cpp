#include "hip/hip_runtime.h"
#include <stdio.h>
#include "hip/hip_runtime.h"

// TODO! Change macro to 0 and see how the timings change without the pinned host memory
#define USE_PINNED_HOST_MEM 0

__global__ void kernel(float *a, int offset)
{
  int i = offset + threadIdx.x + blockIdx.x*blockDim.x;
  float x = (float)i;
  float s = sinf(x); 
  float c = cosf(x);
  a[i] = a[i] + sqrtf(s*s+c*c);
}

float maxError(float *a, int n) 
{
  float maxE = 0;
  for (int i = 0; i < n; i++) {
    float error = fabs(a[i]-1.0f);
    if (error > maxE) maxE = error;
  }
  return maxE;
}

int main(int argc, char **argv)
{
  const int blockSize = 256, nStreams = 4;
  const int n = 4 * 1024 * blockSize * nStreams;
  const int bytes = n * sizeof(float);
   
  int devId = 0;
  if (argc > 1) devId = atoi(argv[1]);

  hipDeviceProp_t prop;
  hipGetDeviceProperties(&prop, devId);
  printf("Device : %s\n", prop.name);
  hipSetDevice(devId);
  
  // Allocate pinned host memory and device memory
  float *a, *d_a;

  #if USE_PINNED_HOST_MEM == 1
    hipHostMalloc((void**)&a, bytes);      // host pinned
  #else
    a=(float *)malloc(n * sizeof(float));  // host pageable
  #endif
  hipMalloc((void**)&d_a, bytes);          // device pinned

  float duration; 
  
  // Create events
  hipEvent_t startEvent, stopEvent;
  hipEventCreate(&startEvent);
  hipEventCreate(&stopEvent);
  
  // Sequential transfer and execute
  memset(a, 0, bytes);
  hipEventRecord(startEvent,0);
  hipMemcpy(d_a, a, bytes, hipMemcpyHostToDevice);
  hipLaunchKernelGGL(kernel, n/blockSize, blockSize, 0, 0, d_a, 0);
  hipMemcpy(a, d_a, bytes, hipMemcpyDeviceToHost);
  hipEventRecord(stopEvent, 0);
  hipEventSynchronize(stopEvent);
  hipEventElapsedTime(&duration, startEvent, stopEvent);
  printf("Duration for sequential transfer and execute: %f (ms)\n", duration);
  printf("  max error: %e\n", maxError(a, n));

  // TODO: Create `nStream` streams here (nStream is defined already to be 4)
  hipStream_t streams[nStreams];
  for(int i = 0; i < nStreams; ++i){
        hipStreamCreate(&streams[i]);
  }


  // Async case 1: loop over {kernel}
  {
    memset(a, 0, bytes);
   
    hipEventRecord(startEvent,0);
    hipMemcpy(d_a, a, bytes, hipMemcpyHostToDevice);
  
    // TODO: loop over nStreams and split the case 1 kernel for 4 kernel calls (one for each stream)
    // TODO: Each stream should handle 1/nStreams of work
    const int streamSize = n / nStreams;

    for(int call = 0; call < nStreams; ++call){
      // i). kernel name
      // ii). 3D-grid dimensions
      // iii). 3D-block dimensions
      // iv). amount of additional shared memory to allocate when launching the kernal
      // v). stream where the kernel should execute
      //     => if 0 then the NULL stream
        hipLaunchKernelGGL(kernel, 
                           streamSize / blockSize, 
                           blockSize, 
                           0, 
                           streams[call], 
                           d_a, call *  streamSize);
    }
  
    hipMemcpy(a, d_a, bytes, hipMemcpyDeviceToHost);
    hipEventRecord(stopEvent, 0);
   
    hipEventSynchronize(stopEvent);
    hipEventElapsedTime(&duration, startEvent, stopEvent);
    printf("Case 1 - Duration for asynchronous kernels: %f (ms)\n", duration);
    printf("  max error: %e\n", maxError(a, n));
  }

  // Async case 2: loop over {async copy, kernel, async copy}
{
    memset(a, 0, bytes);

    const int streamSize = n / nStreams;
    const int streamByte = sizeof(float) * streamSize;
  
    hipEventRecord(startEvent, 0);


    // create one loop
    // TODO: Here split also the memcopies for each stream 
    // TODO: Ie, looping over {async copy, kernel, async copy}
    for(int i = 0; i < nStreams; ++i){

        // calculating offset for job splitting
        int offset = i * streamSize;

        // copy from host to device using streams asynchronously
        // memcopies
        // TODO: Same as case 1, except use asynchronous memcopies 
        hipMemcpyAsync(&d_a[offset], &a[offset], streamByte, hipMemcpyHostToDevice, streams[i]);

        // launch the kernel
        hipLaunchKernelGGL(kernel, streamSize / blockSize, blockSize, 0, streams[i], d_a, offset);

        // copy from device to host asynchronously
        hipMemcpyAsync(&a[offset], &d_a[offset], streamByte, hipMemcpyDeviceToHost, streams[i]);
    }

    // TODO: You should also add the missing hipEvent function calls (cf. case 1)
    hipEventRecord(stopEvent, 0);
    hipEventSynchronize(stopEvent);  // NOTE! stop before synchronizing
    hipEventElapsedTime(&duration, startEvent, stopEvent);  // calculating the time


    printf("Case 2 - Duration for asynchronous transfer+kernels: %f (ms)\n", duration);
    printf("  max error: %e\n", maxError(a, n));
  }

  // Async case 3: loop over {async copy}, loop over {kernel}, loop over {async copy}
  {
    memset(a, 0, bytes);
    // TODO: Same as case 2, except create 3 loops over the streams
    // TODO: Ie, loop 1 {async copy} loop 2 {kernel}. loop 3 {async copy}
    // TODO: You should also add the missing hipEvent function calls (cf. case 1)
    
    const int streamSize = n / nStreams;
    const int streamBytes = sizeof(float) * streamSize;


    hipEventRecord(startEvent, 0);

    for(int i = 0; i < nStreams; ++i){
        // copy from host to device using streams asynchronously
        // memcopies
        // TODO: Same as case 1, except use asynchronous memcopies 
        hipMemcpyAsync(&d_a[i * streamSize], &a[i * streamSize], streamBytes, hipMemcpyHostToDevice, streams[i]);
    }

    for(int i = 0; i < nStreams; ++i){
        // launch the kernel
        hipLaunchKernelGGL(kernel, streamSize / blockSize, blockSize, 0, streams[i], d_a, i * streamSize);    
    }

    for(int i = 0; i < nStreams; ++i){
        // copy from device to host asynchronously
        hipMemcpyAsync(&a[i * streamSize], &d_a[i * streamSize], streamBytes, hipMemcpyDeviceToHost, streams[i]);
    }
    
    hipEventRecord(stopEvent, 0);
    hipEventSynchronize(stopEvent);
    hipEventElapsedTime(&duration, startEvent, stopEvent);

    printf("Case 3 - Duration for asynchronous transfer+kernels: %f (ms)\n", duration);
    printf("  max error: %e\n", maxError(a, n));
  }

  // Clean memory
  hipEventDestroy(startEvent);
  hipEventDestroy(stopEvent);
  hipFree(d_a);
  hipHostFree(a);

  // TODO: Destroy streams here
  for (int i = 0; i < nStreams; ++i){
      hipStreamDestroy(streams[i]);
  }


  return 0;
}
