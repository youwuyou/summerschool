---
Current maintainer: youwuyou (youwuyou@ethz.ch)
In relation to lecture by: CSC Finnland
---




# CSC Summer School in High-Performance Computing 2022

This is the material repository for the high-performance computing summer school by CSC - Finnish IT Center for Science.

Once forked to yourself, you can sync with the original repository (in case of updates) by running:
```
git pull https://github.com/csc-training/summerschool.git
```



# **Exercise Overview**

 - [General instructions](exercise-instructions.md)
 - [Using version control and unix](unix-version-control)
 - [MPI](mpi)
 - [Parallel I/O](parallel-io)
 - [Hybrid MPI/OpenMP](hybrid)
 - [GPU programming with OpenMP](gpu-openmp)
 - [GPU programming with HIP](gpu-hip)


### Chapter 1: MPI

| Topic | Name | Finished |
| --- | --- | --- |
| Introduction | Hello world | :heavy_check_mark: |
| Point-to-point communication | simple message exchange | :heavy_check_mark: |
| Point-to-point communication | simple parallel pi | :heavy_check_mark: |
| Communication patterns | message chain | :heavy_check_mark: |
| Communication patterns | parallel pi | :white_check_mark:	 |
| Communication patterns | broadcast and scatter |  |
| Collective operations | collective operations | :heavy_check_mark: |
| Custom communicators | communicators and collectives |  |
| Heat equation | parallel heat equation solver |  |
| Heat equation | heat equation solver with sendrecv |  |
| Heat equation | collective communication in heat equation solver |  |
| Simple derived types | simple datatypes | :white_check_mark:	 |
| advanced derived types | communicating struct/derived type | :heavy_check_mark: |
| advanced derived types | modifying extent |  |
| process topologies | cartesian grid process topology | :heavy_check_mark: |
| process topologies | message chain with Cartesian communicator |  |
| Non-blocking communication | Non-blocking message chain |  |
| Non-blocking communication | message chain with persistent communication |  |
| Heat equation | heat equation with cartesian communicator |  |
| Heat equation | non-blocking communication in heat equation |  |
| Heat equation | 2D-decomposed heat equation |  |




### Chapter 2: Parallel I/O

| Topic | Name | Finished |
| --- | --- | --- |
| Intermediate level | Parallel I/O with Posix | :white_check_mark: |
| Intermediate level | Simple MPI-IO |  |
| High-level | HDF5 example |  |
|  | Bonus: Checkpoint + restart with MPI-IO |  |

![image](https://user-images.githubusercontent.com/82619264/176366882-a0745170-2416-4fa1-9c1d-be8ca1c37be3.png)



### Chapter 3: Hybrid MPI/OpenMP

| Topic | Name | Finished |
| --- | --- | --- |
| Intro OpenMP | hello world | :heavy_check_mark: |
| Intro OpenMP | work sharing and vector addition | :heavy_check_mark: |
| Library functions | OpenMP library functions | :heavy_check_mark: |
| Data sharing | Data sharing and parallel regions | :heavy_check_mark: |
| Data sharing | race condition in parallel sum | :heavy_check_mark: |
| Reductions and execution controls | reduction | :heavy_check_mark: |
| Reductions and execution controls | execution controls | :heavy_check_mark: |
| Heat equation | fine grain parallelization |  |
| Heat equation | coarse grain parallelization |  |
| Hybrid MPI+OpenMP programming | hybrid hello world |  |
| Hybrid MPI+OpenMP programming | multiple thread communication |  |
| OpenMP tasks | simple tasking |  |
| OpenMP tasks | Parallelizing Mandelbrot with tasks |  |
| OpenMP tasks | Parallel Fibonacci |  |
| Hybrid heat equation | hybrid heat equation |  |



### Chapter 4: GPU programming with OpenMP

| Topic | Name | Finished |
| --- | --- | --- |
| Intro to GPUs in HPC | device query | :white_check_mark: |
| Basics of OpenMP offloading | Hello world | :heavy_check_mark: |
| Basics of OpenMP offloading | vector addition |  |
| Basics of OpenMP offloading | simple offloading for Laplace equation |  |
| Controlling data movement | dot product | |
| Controlling data movement | sum and dot product | |
| Controlling data movement | offloading the heat equation | |
| Unstructed data | unstructed data in heat equation | |
| Device functions | device functions | |
| Interoperability with libraries | using CUDA library | |
| Asynchronous operations | Asynchronous operations | |
| Using multiple GPUS | multi-GPU parallelization for heat equation | |


### Chapter 5: GPU programming with HIP

| Topic | Name | Finished |
| --- | --- | --- |
| Basics of HIP programming | hello world | :heavy_check_mark: |
| Basics of HIP programming | Kernel: saxpy | :heavy_check_mark: |
| Basics of HIP programming | Kernel: copy2d | :heavy_check_mark: |
| Synchronisation and streams | investigating streams and events | :heavy_check_mark: |
| Memory management | memory management strategies | :white_check_mark: |
| Memory management | unified memory and structs | :heavy_check_mark: |
| Fortran and HIP | Hipfort: saxpy | :heavy_check_mark: |
| Multi-GPU programming | vector sum on two GPUs without MPI | :heavy_check_mark: |
| Multi-GPU programming | ping-pong with multiple GPUs and MPI |  |
| Multi-GPU programming | peer to peer device access |  |
| Multi-GPU programming | Bonus: Heat equation with HIP |  |



## Others
for more theoretical aspects see my [side-notes](https://github.com/youwuyou/summerschool/wiki) 
 
 
 
---
## Notes
- [x] Have fun!
