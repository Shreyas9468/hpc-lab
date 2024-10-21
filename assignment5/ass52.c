#include<omp.h>
#include<stdio.h>

int main(){

 int Arybhatta =10;

int num_thread = 5;

#pragma omp parallel num_threads(num_thread) private(Arybhatta)
{
    Arybhatta=10;
    int thread_id = omp_get_thread_num();
    int value = Arybhatta * thread_id;
    printf("Value of multiplication : %d\n " ,value);
}
printf("End of program");


}
