#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define BUFFERSIZE 5

int bufferSize = 5;
int numItems = 10;
int buffer[BUFFERSIZE];
int count = 0;

void producer(){
  for(int i=0; i<numItems; i++){
    int item = i;
    int produced = 0;
    while(!produced){
      #pragma omp critical
      {
        if(count < bufferSize){
          buffer[count] = item;
          printf(" + Produced item : %d\n", item);
          count++;
          produced = 1;
        }
      }
      #pragma omp flush
    }
  }
}

void consumer(){
  for(int i=0; i<numItems; i++){
    int item;
    int consumed = 0;
    while (!consumed) {
      #pragma omp critical
      {
        if(count > 0){
          item = buffer[count-1];
          printf(" - Consumed item : %d\n", item);
          count--;
          consumed = 1;
        }
      }
      #pragma omp flush
    }
  }
}

int main(int argc, char *argv[])
{
  omp_set_num_threads(2);

  #pragma omp parallel sections
  {

    #pragma omp section 
    {
      producer();
    }

    #pragma omp section 
    {
      consumer();
    }

  }
  return EXIT_SUCCESS;
}