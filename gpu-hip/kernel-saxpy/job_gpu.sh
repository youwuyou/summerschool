#!/bin/bash
#SBATCH --job-name=d_query
#SBATCH --account=project_2000745
#SBATCH --reservation=summerschool-gpu
#SBATCH --partition=gpu
#SBATCH --time=00:05:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=10
#SBATCH --mem-per-cpu=8000
#SBATCH --gres=gpu:v100:1

module load hip
srun saxpy

# srun nvidia-smi