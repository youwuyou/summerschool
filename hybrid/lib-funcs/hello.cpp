#include <cstdio>
#include <omp.h>
#include <iostream>

int main()
{
    printf("Hello world!\n");
    omp_set_num_threads(4);

    int tid, nthreads;

    #pragma omp parallel private(tid) shared(nthreads)
        {
            tid = omp_get_thread_num();

            // Print out the total number of active threads as well as the ID of each thread.
            // Approach 1: specifying using the thread numbering
            // if (tid == 0){
            //     int nthreads = omp_get_num_threads();
            //     std::cout << "Total number of threads is: " << nthreads << std::endl;
            // }

            // Approach 2: using directives
            #pragma omp single
            nthreads = omp_get_num_threads();

            #pragma omp critical
            std::cout << "call from thread no." << tid << std::endl;
        }
    std::cout << "There were " << nthreads << " threads in all." << std::endl;


    return 0;
}





//`omp_get_num_threads()` and `omp_get_thread_num()` library functions.
