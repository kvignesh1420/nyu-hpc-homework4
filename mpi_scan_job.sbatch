#!/bin/bash

#SBATCH --job-name=mpi_scan
#SBATCH --nodes=10
#SBATCH --tasks-per-node=1
#SBATCH --mem=2GB
#SBATCH --time=01:00:00
#SBATCH --verbose

module purge
module load amber/openmpi/intel/20.06

# change the size of array here
# mpirun ./mpi_scan 100000
mpirun ./mpi_scan 1000000