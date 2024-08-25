#include <stdio.h>
#include <omp.h>

void res(long long num_steps){
    
    double step = 1.0/(double)num_steps;
    double sum = 0.0;
    double start = omp_get_wtime();
    #pragma omp parallel
    {
        double x;
        #pragma omp for reduction(+:sum)
        for (int i = 0; i < num_steps; i++) {
            x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    }
    double end = omp_get_wtime();

    double pi = step * sum;

    printf("Calculated value of Pi: %.15f\n", pi);
    printf("Time taken: %.6f seconds\n", end - start);
}
int main() {
    res(100000000);
    res(1000000);
    res(1000000000);
    return 0;
}
