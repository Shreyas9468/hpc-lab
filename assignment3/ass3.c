#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Function to compare two integers (used for qsort)
int compareAsc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int compareDesc(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

void res(int n , int numThreads){
    int *a = (int*) malloc(n * sizeof(int));
  int *b = (int*) malloc(n * sizeof(int));

  for(int i=0; i<n; i++){
    a[i] = i+1;
    b[i] = n-i;
  }

    // Sort vector 'a' in ascending order
    qsort(a, n, sizeof(int), compareAsc);

    // Sort vector 'b' in descending order
    qsort(b, n, sizeof(int), compareDesc);

    // Parallel calculation of the minimum scalar product
    int minScalarProduct = 0;
     omp_set_num_threads(numThreads);
     double start = omp_get_wtime();
    #pragma omp parallel for reduction(+:minScalarProduct)
    for(int i = 0; i < n; i++) {
        minScalarProduct += a[i] * b[i];
    }



    double  entd = omp_get_wtime();
     printf("Compeleted Calculation with n:%d threads:%d in %f seconds\n", n, numThreads, entd - start);
    printf("Minimum Scalar Product: %d\n", minScalarProduct);


}

int main() {


    res(10000000, 1);
  res(10000000, 4);
  res(10000000, 8);
  res(10000000, 12);
    return 0;
}
