#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void fun(int n, int numThreads){
  int **mat1 = (int**)malloc(n * sizeof(int*));
  int **mat2 = (int**)malloc(n * sizeof(int*));
  int **ans = (int**)malloc(n * sizeof(int*));

  for (int i = 0; i < n; i++) {
    mat1[i] = (int*)malloc(n * sizeof(int));
    mat2[i] = (int*)malloc(n * sizeof(int));
    ans[i] = (int*)malloc(n * sizeof(int));
  }
  omp_set_num_threads(numThreads);

  double start = omp_get_wtime();

  #pragma omp parallel for 
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++){
      ans[i][j] = mat1[i][j] + mat2[i][j];
    }
  }

  double end = omp_get_wtime();

  printf("Time taken for n:%d threads:%d : %f \n", n, numThreads, end - start);

  for (int i = 0; i < n; i++) {
    free(mat1[i]);
    free(mat2[i]);
    free(ans[i]);
  }
  free(mat1);
  free(mat2);
  free(ans);

  return;
}

int main(int argc, char *argv[])
{
  int matSizes[] = {250, 500, 750, 1000, 2000};
  int numThreads[] = {2, 4, 8};
  for(int i=0; i<5; i++){
    printf("\nCalculations for matrix size %d : \n", matSizes[i]);
    for(int j=0; j<3; j++){
      fun(matSizes[i], numThreads[j]);
    }
  }
  return EXIT_SUCCESS;
}