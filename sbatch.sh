#!/bin/bash

#SBATCH -N 1
#SBATCH --ntasks-per-node=4
#SBATCH -t 00:10

./primality 6