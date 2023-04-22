// scan functionality using MPI
// ring communication on integers and integer arrays
#include <math.h>
#include <stdio.h>
#include <cstdlib>
#include <mpi.h>
#include <iostream>

double mpi_scan(MPI_Comm comm, int rank, int comm_size, int N){
    double* rand_array = nullptr;
    double* scan_rand_array = nullptr;
    MPI_Barrier(comm);
    if(rank==0) {
        rand_array = (double*)malloc(N * sizeof(double));
        scan_rand_array = (double*)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++) {

            rand_array[i] = drand48();

            // comment the above line and uncomment the below line for simpler
            // integer based scan

            // rand_array[i] = i;
        }
    }
    int items_per_rank = N/comm_size;
    double* local_array = (double*)malloc(items_per_rank * sizeof(double));
    double* offsets = (double*)malloc(comm_size * sizeof(double));
    double local_sum = 0.0;

    // start time after setup of data buffers
    double tt = MPI_Wtime();
    // scatter random vector from root rank 0
    MPI_Scatter(rand_array, items_per_rank, MPI_DOUBLE, local_array,
            items_per_rank, MPI_DOUBLE, 0, comm);

    // compute offsets per rank
    for (int i = 1; i < items_per_rank; i++) {
        local_array[i] += local_array[i-1];
        // printf("Rank: %d local_array[%d]=%f\n", rank, i, local_array[i]);
    }
    local_sum = local_array[items_per_rank-1];

    MPI_Barrier(comm);
    // Allgather the offsets
    MPI_Allgather(&local_sum, 1, MPI_DOUBLE, offsets, 1, MPI_DOUBLE, comm);

    // cumulative offsets
    for(int i=1; i < comm_size; i++){
        offsets[i] += offsets[i-1];
    }

    // update local copies with the offsets
    if(rank!=0){
        for (int i = 0; i < items_per_rank; i++) {
            local_array[i] += offsets[rank-1];
            // printf("After updates Rank: %d local_array[%d]=%f\n", rank, i, local_array[i]);
        }
    }


    MPI_Barrier(comm);
    // send back the data to rank0
    MPI_Gather(local_array, items_per_rank, MPI_DOUBLE, scan_rand_array,
                items_per_rank, MPI_DOUBLE, 0, comm);

    // MPI_Barrier(comm);
    tt = MPI_Wtime() - tt;

    // validate the MPI based scan with actual sequential scan
    if(rank==0) {
        double error = 0.0;
        for (int i = 1; i < N; i++) {
            rand_array[i] += rand_array[i-1];
            // handle precision errors for doubles
            error += fabs(rand_array[i] - scan_rand_array[i]);
        }
        printf("Total error between sequential and MPI scans: %f\n", error);
    }

    free(rand_array);
    free(scan_rand_array);
    free(local_array);
    free(offsets);

    return tt;
}


int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  if (argc != 2) {
    printf("Usage: mpirun ./mpi_scan <N>\n");
    abort();
  }
//   size of the array set by the user
  int N = atoi(argv[1]);

  int rank, comm_size;
  MPI_Comm comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &comm_size);

  /* get name of host running MPI process */
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  MPI_Get_processor_name(processor_name, &name_len);
  printf("Rank %d/%d running on %s.\n", rank, comm_size, processor_name);

  MPI_Barrier(comm);
  if(rank==0) printf("Size of the array: %d\n", N);
  double tt;

  tt = mpi_scan(comm, rank, comm_size, N);
  if(rank==0) {
    printf("MPI scan latency: %e ms\n", tt * 1000);
    printf("MPI scan bandwidth: %e GB/s\n", N/tt/1e9);
  }

  MPI_Finalize();
}

