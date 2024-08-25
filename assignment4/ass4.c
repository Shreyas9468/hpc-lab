#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void fun(int n){
  int vec[n];
  vec[0] = 0;
  vec[1] = 1;

  #pragma omp for schedule(dynamic, 1)
  for(int i=2; i<n; i++){
    #pragma omp critical
    {
      vec[i] = vec[i-1] + vec[i-2];
      printf("F(%d) = %d -- computed by thread %d\n", i, vec[i], omp_get_thread_num());
    }
  }

  #pragma omp bvecier

  return;
}

int main(int argc, char *argv[])
{
  fun(10);
  return EXIT_SUCCESS;
}