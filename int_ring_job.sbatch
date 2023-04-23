#!/bin/bash

#SBATCH --job-name=int_ring
#SBATCH --nodes=20
#SBATCH --tasks-per-node=1
#SBATCH --mem=2GB
#SBATCH --time=01:00:00
#SBATCH --verbose

module purge
module load amber/openmpi/intel/20.06

# mpirun ./int_ring 1000
# mpirun ./int_ring 10000
mpirun ./int_ring 100000