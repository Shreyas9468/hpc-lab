#include <stdio.h>
#include <math.h>
#include "mpi.h"
#define N 8

void transpose(double *data, int n) {
    int i, j;
    double tmp;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            tmp = data[i * n + j];
            data[i * n + j] = data[j * n + i];
            data[j * n + i] = tmp;
        }
    }
}

void four1(double *data, int nn, int isign) {
    int n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta;
    double tempr, tempi;
    n = nn << 1;
    j = 1;
    for (i = 1; i < n; i += 2) {
        if (j > i) {
            tempr = data[j - 1];
            data[j - 1] = data[i - 1];
            data[i - 1] = tempr;
            tempr = data[j];
            data[j] = data[i];
            data[i] = tempr;
        }
        m = n >> 1;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }
    mmax = 2;
    while (n > mmax) {
        istep = mmax << 1;
        theta = isign * (6.28318530717959 / mmax);
        wtemp = sin(0.5 * theta);
        wpr = -2.0 * wtemp * wtemp;
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for (m = 1; m < mmax; m += 2) {
            for (i = m; i <= n; i += istep) {
                j = i + mmax;
                tempr = wr * data[j - 1] - wi * data[j];
                tempi = wr * data[j] + wi * data[j - 1];
                data[j - 1] = data[i - 1] - tempr;
                data[j] = data[i] - tempi;
                data[i - 1] += tempr;
                data[i] += tempi;
            }
            wr = (wtemp = wr) * wpr - wi * wpi + wr;
            wi = wi * wpr + wtemp * wpi + wi;
        }
        mmax = istep;
    }
}

int main(int argc, char **argv) {
    int rank, numnodes, namelen, i, j, rc;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    double dataR[N * N], dataI[N * N];
    MPI_Status status;
    rc = MPI_Init(&argc, &argv);
    if (rc != MPI_SUCCESS) {
        MPI_Abort(MPI_COMM_WORLD, rc);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &numnodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    if (rank == 0) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                dataR[i * N + j] = i * N + j;
                dataI[i * N + j] = 0.0;
            }
        }
    }

    MPI_Bcast(dataR, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(dataI, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double start_time = MPI_Wtime();
    for (i = rank; i < N; i += numnodes) {
        four1(&dataR[i * N], N, 1);
        four1(&dataI[i * N], N, 1);
    }

    MPI_Gather(&dataR[rank * N], N * N / numnodes, MPI_DOUBLE, dataR, N * N / numnodes, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&dataI[rank * N], N * N / numnodes, MPI_DOUBLE, dataI, N * N / numnodes, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        transpose(dataR, N);
        transpose(dataI, N);
    }

    MPI_Bcast(dataR, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(dataI, N * N, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (i = rank; i < N; i += numnodes) {
        four1(&dataR[i * N], N, 1);
        four1(&dataI[i * N], N, 1);
    }

    MPI_Gather(&dataR[rank * N], N * N / numnodes, MPI_DOUBLE, dataR, N * N / numnodes, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&dataI[rank * N], N * N / numnodes, MPI_DOUBLE, dataI, N * N / numnodes, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    double end_time = MPI_Wtime();

    if (rank == 0) {
        printf("Result after 2D FFT (Real part):\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%2.0f ", dataR[i * N + j]);
            }
            printf("\n");
        }
        printf("Execution time with %d processes: %f seconds\n", numnodes, end_time - start_time);
    }

    MPI_Finalize();
    return 0;
}
