// ring communication on integers and integer arrays
#include <stdio.h>
#include <cstdlib>
#include <mpi.h>
#include <iostream>

double single_int_ring(MPI_Comm comm, int rank, int comm_size, int N){

    int message = 0;
    MPI_Barrier(comm);
    double tt = MPI_Wtime();
    for(long repeat = 0; repeat < N; repeat++){
        MPI_Status status;
        if (rank == 0) {
            if(repeat == 0){
                MPI_Send(&message, 1, MPI_INT, (rank+1)%comm_size, repeat, comm);
            }
            else{
                MPI_Recv(&message, 1, MPI_INT, (rank-1)%comm_size, repeat-1, comm, &status);
                message += rank;
                MPI_Send(&message, 1, MPI_INT, (rank+1)%comm_size, repeat, comm);
            }
        } else {
            MPI_Recv(&message, 1, MPI_INT, (rank-1)%comm_size, repeat, comm, &status);
            message += rank;
            MPI_Send(&message, 1, MPI_INT, (rank+1)%comm_size, repeat, comm);
        }
    }
    // receive final message
    if (rank == 0) {
        MPI_Status status;
        MPI_Recv(&message, 1, MPI_INT, (rank-1)%comm_size, N-1, comm, &status);
    }
    tt = MPI_Wtime() - tt;
    // do not count the print op in mpi timings
    if (rank == 0){
        int desired_output = N*((comm_size-1)*(comm_size))/2;
        printf("comm_size=%d, N=%d, desired_output=%d, final_message=%d\n",
                comm_size, N, desired_output, message);
    }

    return tt;
}

double array_int_ring(MPI_Comm comm, int rank, int comm_size, int N, int array_size){

    MPI_Barrier(comm);
    int* message = (int*) malloc(sizeof(int)*array_size);
    for (long i = 0; i < array_size; i++) message[i] = 0;

    double tt = MPI_Wtime();
    for(long repeat = 0; repeat < N; repeat++){
        MPI_Status status;
        if (rank == 0) {
            if(repeat == 0){
                MPI_Send(message, array_size, MPI_INT, (rank+1)%comm_size, repeat, comm);
            }
            else{
                MPI_Recv(message, array_size, MPI_INT, (rank-1)%comm_size, repeat-1, comm, &status);
                for (long i = 0; i < array_size; i++) message[i] += rank;
                MPI_Send(message, array_size, MPI_INT, (rank+1)%comm_size, repeat, comm);
            }
        } else {
            MPI_Recv(message, array_size, MPI_INT, (rank-1)%comm_size, repeat, comm, &status);
            for (long i = 0; i < array_size; i++) message[i] += rank;
            MPI_Send(message, array_size, MPI_INT, (rank+1)%comm_size, repeat, comm);
        }
    }
    // receive final message
    if (rank == 0) {
        MPI_Status status;
        MPI_Recv(message, array_size, MPI_INT, (rank-1)%comm_size, N-1, comm, &status);
    }
    tt = MPI_Wtime() - tt;

    // check if all entries are the same in the received array and print it.
    // the print op is not accounted in the MPI latencies
    if(rank == 0){
        for (int i = 0; i < array_size-1; i++){
            if(message[i] != message[i+1]){
                printf("The final message is incorrect\n");
                printf("message[%d] = %d\n", i, message[i]);
                printf("message[%d] = %d\n", i+1, message[i+1]);
                return tt;
            }
        }
        printf("The final message is same across all entries\n");
        int desired_output = N*((comm_size-1)*(comm_size))/2;
        printf("comm_size=%d, N=%d, desired_output=%d, message[0]=%d\n",
                comm_size, N, desired_output, message[0]);
    }

    free(message);
    return tt;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  if (argc != 2) {
    printf("Usage: mpirun ./int_ring <N>\n");
    abort();
  }
//   repeat count set by the user
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
  if(rank==0) printf("Number of repeats: %d\n", N);
  double tt;
  tt = single_int_ring(comm, rank, comm_size, N);
  if(rank==0) printf("single_int ring latency: %e ms\n", tt/N * 1000);

  MPI_Barrier(comm);
  // 500,000 integer array is approximately 2MB
  int array_size = 500000;
  tt = array_int_ring(comm, rank, comm_size, N, array_size);
  if(rank==0) {
    printf("array_int ring latency: %e ms\n", tt/N * 1000);
    printf("array_int ring bandwidth: %e GB/s\n", (array_size*N)/tt/1e9);
  }

  MPI_Finalize();
}

