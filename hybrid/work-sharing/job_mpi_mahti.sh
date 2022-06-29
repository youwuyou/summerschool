#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=project_2000745
#SBATCH --partition=medium
#SBATCH --reservation=summerschool
#SBATCH --time=00:05:00
#SBATCH --ntasks=1

# srun CH --job-name=example
# srun --job-name=example --account=project_2000745 --partition=medium --reservation=summerschool --time=00:05:00 --ntasks=1

OMP_NUM_THREADS=20 ./program

# alias runexample='srun --job-name=example --account=project_2000745 --partition=medium --reservation=summerschool --time=00:05:00 --ntasks=1'
