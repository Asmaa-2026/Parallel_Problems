#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#define NUMBER_OF_TESTS 10

int main(int argc, char *argv[]) {
    double *buf; int rank, numprocs, n; double t1, t2;
    int j, k, nloop; MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    if (numprocs != 2) { printf("Need 2 processes\n"); return 0; }
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) printf("\tn\ttime [sec]\tRate [Mb/sec]\n");
    for (n = 1; n < 100000000; n *= 2) {
        nloop = 1000000 / n; if (nloop < 1) nloop = 1;
        buf = (double *)malloc(n * sizeof(double));
        for (k = 0; k < NUMBER_OF_TESTS; k++) {
            if (rank == 0) {
                t1 = MPI_Wtime();
                for (j = 0; j < nloop; j++)
                    MPI_Send(buf, n, MPI_DOUBLE, 1, k, MPI_COMM_WORLD);
                t2 = (MPI_Wtime() - t1) / nloop;
            } else {
                for (j = 0; j < nloop; j++)
                    MPI_Recv(buf, n, MPI_DOUBLE, 0, k, MPI_COMM_WORLD, &status);
            }
        }
        if (rank == 0) {
            double bw = n * sizeof(double) * 1.0e-6 * 8 / t2;
            printf("\t%10d\t %10.8f\t%8.2f\n", n, t2, bw);
        }
        free(buf);
    }
    MPI_Finalize(); return 0;
}
