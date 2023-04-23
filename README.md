## Homework 4

### Setup
Greene Supercomputing cluster

```bash
[vk2115@log-3 homework4]$ module list

Currently Loaded Modules:
  1) gcc/10.2.0   2) openmpi/gcc/4.0.5
```

### Question 1: Greene network test

I modified the pingpong example from class to print the nodes on which each MPI process is running.

To run the slurm job:
```bash
$ [vk2115@log-3 homework4]$ sbatch pingpong_job.sbatch
```

The output of running on different nodes is as follows:
```bash
Rank 0/2 running on cs498.hpc.nyu.edu.
Rank 1/2 running on cs499.hpc.nyu.edu.
pingpong latency: 1.065362e-03 ms
pingpong bandwidth: 1.222926e+01 GB/s
```

Additionally, the output of running on same nodes is as follows:
```bash
Rank 1/2 running on cs008.hpc.nyu.edu.
Rank 0/2 running on cs008.hpc.nyu.edu.
pingpong latency: 3.114100e-04 ms
pingpong bandwidth: 1.031490e+01 GB/s
```

### Question 2: Ring Communication

Single integer and integer array communication across processes in a ring.

Submit the job using:
```bash
$ [vk2115@log-3 homework4]$ sbatch int_ring_job.sbatch
```

Output:

RUN 1: `size=10, N=1000`

```bash
Rank 0/10 running on cs044.hpc.nyu.edu.
Rank 3/10 running on cs349.hpc.nyu.edu.
Rank 1/10 running on cs206.hpc.nyu.edu.
Rank 2/10 running on cs348.hpc.nyu.edu.
Rank 4/10 running on cs382.hpc.nyu.edu.
Rank 9/10 running on cs490.hpc.nyu.edu.
Rank 5/10 running on cs383.hpc.nyu.edu.
Rank 7/10 running on cs392.hpc.nyu.edu.
Rank 6/10 running on cs391.hpc.nyu.edu.
Rank 8/10 running on cs489.hpc.nyu.edu.
Number of repeats: 1000

comm_size=10, N=1000, desired_output=45000, final_message=45000
Time: 0.013418
single_int per-communication latency: 0.001342 ms

The final message is same across all entries
comm_size=10, N=1000, desired_output=45000, message[0]=45000
Time: 2.613323
array_int per-communication latency: 0.261332 ms
array_int per-communication bandwidth: 1.913273 GB/s
```

RUN 2: `size=10, N=10000`

```bash
Rank 0/10 running on ga018.hpc.nyu.edu.
Rank 9/10 running on ga027.hpc.nyu.edu.
Rank 6/10 running on ga024.hpc.nyu.edu.
Rank 5/10 running on ga023.hpc.nyu.edu.
Rank 2/10 running on ga020.hpc.nyu.edu.
Rank 8/10 running on ga026.hpc.nyu.edu.
Rank 7/10 running on ga025.hpc.nyu.edu.
Rank 1/10 running on ga019.hpc.nyu.edu.
Rank 4/10 running on ga022.hpc.nyu.edu.
Rank 3/10 running on ga021.hpc.nyu.edu.
Number of repeats: 10000

comm_size=10, N=10000, desired_output=450000, final_message=450000
single_int per-communication latency: 0.001488 ms

The final message is same across all entries
comm_size=10, N=10000, desired_output=450000, message[0]=450000
array_int per-communication latency: 0.226879 ms
array_int per-communication bandwidth: 2.203823 GB/s
```

RUN 3: `size=20, N=10000`

```bash
Rank 0/20 running on cs003.hpc.nyu.edu.
Rank 16/20 running on cs392.hpc.nyu.edu.
Rank 12/20 running on cs349.hpc.nyu.edu.
Rank 7/20 running on cs206.hpc.nyu.edu.
Rank 17/20 running on cs489.hpc.nyu.edu.
Rank 19/20 running on cs495.hpc.nyu.edu.
Rank 10/20 running on cs240.hpc.nyu.edu.
Rank 18/20 running on cs490.hpc.nyu.edu.
Rank 13/20 running on cs382.hpc.nyu.edu.
Rank 1/20 running on cs004.hpc.nyu.edu.
Rank 6/20 running on cs147.hpc.nyu.edu.
Rank 11/20 running on cs348.hpc.nyu.edu.
Rank 4/20 running on cs100.hpc.nyu.edu.
Rank 2/20 running on cs044.hpc.nyu.edu.
Rank 15/20 running on cs391.hpc.nyu.edu.
Rank 14/20 running on cs383.hpc.nyu.edu.
Rank 3/20 running on cs099.hpc.nyu.edu.
Rank 5/20 running on cs146.hpc.nyu.edu.
Rank 9/20 running on cs239.hpc.nyu.edu.
Rank 8/20 running on cs238.hpc.nyu.edu.
Number of repeats: 10000

comm_size=20, N=10000, desired_output=1900000, final_message=1900000
single_int per-communication latency: 0.001403 ms

The final message is same across all entries
comm_size=20, N=10000, desired_output=1900000, message[0]=1900000
array_int per-communication latency: 0.270768 ms
array_int per-communication bandwidth: 1.846597 GB/s
```

RUN 4: `size=20, N=100000`

```bash
Rank 0/20 running on cs003.hpc.nyu.edu.
Rank 16/20 running on cs392.hpc.nyu.edu.
Rank 17/20 running on cs489.hpc.nyu.edu.
Rank 6/20 running on cs206.hpc.nyu.edu.
Rank 1/20 running on cs004.hpc.nyu.edu.
Rank 19/20 running on cs495.hpc.nyu.edu.
Rank 11/20 running on cs348.hpc.nyu.edu.
Rank 12/20 running on cs349.hpc.nyu.edu.
Rank 13/20 running on cs382.hpc.nyu.edu.
Rank 18/20 running on cs490.hpc.nyu.edu.
Rank 8/20 running on cs238.hpc.nyu.edu.
Rank 4/20 running on cs146.hpc.nyu.edu.
Rank 5/20 running on cs147.hpc.nyu.edu.
Rank 7/20 running on cs207.hpc.nyu.edu.
Rank 3/20 running on cs100.hpc.nyu.edu.
Rank 14/20 running on cs383.hpc.nyu.edu.
Rank 2/20 running on cs099.hpc.nyu.edu.
Rank 10/20 running on cs240.hpc.nyu.edu.
Rank 15/20 running on cs391.hpc.nyu.edu.
Rank 9/20 running on cs239.hpc.nyu.edu.
Number of repeats: 100000

comm_size=20, N=100000, desired_output=19000000, final_message=19000000
single_int per-communication latency: 0.001322 ms

The final message is same across all entries
comm_size=20, N=100000, desired_output=19000000, message[0]=19000000
array_int per-communication latency: 0.265607 ms
array_int per-communication bandwidth: 1.882477 GB/s
```


### Question 3: MPI version of Scan

Scan operation on large arrays with double precision random values.

Submit the job using:
```bash
$ [vk2115@log-3 homework4]$  sbatch mpi_scan_job.sbatch
```

RUN 1: `world_size=10, array_size=100000`

```bash
Rank 9/10 running on cs489.hpc.nyu.edu.
Rank 7/10 running on cs455.hpc.nyu.edu.
Rank 6/10 running on cs307.hpc.nyu.edu.
Rank 0/10 running on cs080.hpc.nyu.edu.
Rank 1/10 running on cs302.hpc.nyu.edu.
Rank 5/10 running on cs306.hpc.nyu.edu.
Rank 3/10 running on cs304.hpc.nyu.edu.
Rank 4/10 running on cs305.hpc.nyu.edu.
Rank 8/10 running on cs471.hpc.nyu.edu.
Rank 2/10 running on cs303.hpc.nyu.edu.
Size of the array: 100000
Total error between sequential and MPI scans: 0.000002
MPI scan latency: 2.397701e+01 ms
MPI scan bandwidth: 4.170661e-03 GB/s
```

RUN 2: `world_size=10, array_size=1000000`

```bash
Rank 0/10 running on cs087.hpc.nyu.edu.
Rank 1/10 running on cs239.hpc.nyu.edu.
Rank 2/10 running on cs240.hpc.nyu.edu.
Rank 4/10 running on cs303.hpc.nyu.edu.
Rank 5/10 running on cs304.hpc.nyu.edu.
Rank 3/10 running on cs302.hpc.nyu.edu.
Rank 9/10 running on cs471.hpc.nyu.edu.
Rank 7/10 running on cs306.hpc.nyu.edu.
Rank 6/10 running on cs305.hpc.nyu.edu.
Rank 8/10 running on cs307.hpc.nyu.edu.
Size of the array: 1000000
Total error between sequential and MPI scans: 0.000389
MPI scan latency: 2.298346e+01 ms
MPI scan bandwidth: 4.350954e-02 GB/s
```

Additional sanity check with deterministic values, i.e in the `mpi_scan` function:
```c++
// replace
rand_array[i] = drand48();
// with
rand_array[i] = i;
```

RUN 3: `world_size=10, array_size=1000000`

```bash
Rank 0/10 running on cs146.hpc.nyu.edu.
Rank 7/10 running on cs391.hpc.nyu.edu.
Rank 9/10 running on cs490.hpc.nyu.edu.
Rank 4/10 running on cs348.hpc.nyu.edu.
Rank 5/10 running on cs349.hpc.nyu.edu.
Rank 3/10 running on cs171.hpc.nyu.edu.
Rank 1/10 running on cs147.hpc.nyu.edu.
Rank 2/10 running on cs150.hpc.nyu.edu.
Rank 8/10 running on cs462.hpc.nyu.edu.
Rank 6/10 running on cs382.hpc.nyu.edu.
Size of the array: 1000000
Total error between sequential and MPI scans: 0.000000
MPI scan latency: 1.606138e+01 ms
MPI scan bandwidth: 6.226114e-02 GB/s
```

### Question 4: Project Pitch

**Member(s)**: Vignesh Kothapalli (Will be doing it alone and have discussed the decision with Prof. Georg)

**Objective:** Implement the SketchyCGAL semidefinite programming (SDP) algorithm for finding Max-Cut's in general graphs. The algorithm is based on the "Scalable Semidefinite Programming" paper [1] by Yurtsever et.al.

**Motivation:** One of the most widely studied application of Max-Cut is it's application to the [Ising Model](https://www.wikiwand.com/en/Ising_model). By formulating the lattice of the ferromagentic material as an undirected graph, the max-cut of such a graph allows us to upper bound the total energy of the states of the model (refer [2] for details). However, since the problem is NP-Hard for general graphs, SDP relaxations are employed to obtain approximate solutions. The main challenge with such approaches is that the size of the dense variable matrix is $O(n^2)$ (where $n$ represents the number of nodes in a graph), which prevents us from scaling to larger graphs with SDP approaches. To this end, the authors of [1] designed a randomized Lanczos and Nystrom approximation based algorithm which requires a storage of $O(d + Rn)$. Here $d, R$ are the dimensions of the sketch variables.

**Tasks:**
- Create data loaders for the DIMACS10 graphs [3].
- Implement the Randomized Lanczos algorithm for approximating the minimum eigenvector of a matrix.
- Implement the Randomized Nystrom sketching algorithm for approximating the low-rank SDP solution in a streaming fashion.
- Implement the SketchyCGAL algorithm using the functionality of the above two methods.
- Use the DIMAC10 graphs to compare the cut-values and runtimes with matlab implementation results from [1].

**Tools:** The algorithm will be implemented in C++ and employ sparse/dense matrix data structures from the Eigen C++ library. Finally, I plan on leveraging OpenMP support for Eigen and improve the runtime performance with parallelism.


**References**

1. Yurtsever, Alp, et al. "Scalable semidefinite programming." SIAM Journal on Mathematics of Data Science 3.1 (2021): 171-200.

2. Galluccio, Anna, Martin Loebl, and Jan Vondrák. "Optimization via enumeration: a new algorithm for the max cut problem." Mathematical Programming 90 (2001): 273-290.

3. David A. Bader, Henning Meyerhenke, Peter Sanders, Dorothea Wagner (eds.): Graph Partitioning and Graph Clustering. 10th DIMACS Implementation Challenge Workshop. February 13-14, 2012. Georgia Institute of Technology, Atlanta, GA. Contemporary Mathematics 588. American Mathematical Society and Center for Discrete Mathematics and Theoretical Computer Science, 2013.

