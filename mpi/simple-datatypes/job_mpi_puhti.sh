#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=project_2000745
#SBATCH --partition=medium
#SBATCH --reservation=summerschool
#SBATCH --time=00:05:00
#SBATCH --ntasks=2

srun ./composed
