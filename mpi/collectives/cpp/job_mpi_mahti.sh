#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=project_2000745
#SBATCH --partition=medium
#SBATCH --reservation=summerschool
#SBATCH --time=00:08:00
#SBATCH --ntasks=4

srun ./collective4
