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
| Communication patterns | message chain |  |
| Communication patterns | parallel pi |  |
| Communication patterns | broadcast and scatter |  |
| Collective operations | collective operations |  |
| Custom communicators | communicators and collectives |  |
| Heat equation | parallel heat equation solver |  |
| Heat equation | heat equation solver with sendrecv |  |
| Heat equation | collective communication in heat equation solver |  |
| Simple derived types | simple datatypes |  |
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
|  | Parallel I/O with Posix |  |
|  | Simple MPI-IO |  |
|  | HDF5 example |  |
|  | Bonus: Checkpoint + restart with MPI-IO |  |


### Chapter 3: Hybrid MPI/OpenMP

| Topic | Name | Finished |
| --- | --- | --- |
| Intro OpenMP | hello world |  |
| Intro OpenMP | work sharing and vector addition |  |
| Library functions | OpenMP library functions |  |
| Data sharing | Data sharing and parallel regions |  |
| Data sharing | race condition in parallel sum |  |
| Reductions and execution controls | reduction |  |
| Reductions and execution controls | execution controls |  |
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
| Code exercise 1 |  |  |


### Chapter 5: GPU programming with HIP

| Topic | Name | Finished |
| --- | --- | --- |
| Code exercise 1 |  |  |




## Others
for more theoretical aspects see my [side-notes](https://github.com/youwuyou/summerschool/wiki) 
 
 
 
---
## Notes
- [x] Have fun!
