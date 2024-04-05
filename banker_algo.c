#include <stdio.h>
#include <stdlib.h>

int **allocation;
int **max;
int **available;
int **need;

void initialize(int processNo, int resourceNo)
{
  allocation = (int**)malloc(processNo * sizeof(int*));
  max = (int**)malloc(processNo * sizeof(int*));
  available = (int**)malloc(processNo * sizeof(int*));
  need = (int**)malloc(processNo * sizeof(int*));

  for (int i = 0; i < resourceNo; i++)
  {
    allocation[i] = (int*)malloc(resourceNo * sizeof(int));
    max[i] = (int*)malloc(resourceNo * sizeof(int));
    available[i] = (int*)malloc(resourceNo * sizeof(int));
    need[i] = (int*)malloc(resourceNo * sizeof(int));
  }
}