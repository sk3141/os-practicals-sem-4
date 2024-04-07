#include <stdio.h>
#include <stdlib.h>

int **allocation;
int **max;
int **available;
int **need;
int *safeSequence;
int* executed;
int currentResourceIndex = 0;
int curSafe = 0;

void initialize(int processNo, int resourceNo)
{
  allocation = (int**)malloc(processNo * sizeof(int*));
  max = (int**)malloc(processNo * sizeof(int*));
  available = (int**)malloc(processNo * sizeof(int*) + 1);
  need = (int**)malloc(processNo * sizeof(int*));
  safeSequence = (int*)malloc(processNo * sizeof(int));
  executed = (int*)malloc(processNo * sizeof(int));

  for (int i = 0; i < processNo; i++)
  {
    allocation[i] = (int*)malloc(resourceNo * sizeof(int));
    max[i] = (int*)malloc(resourceNo * sizeof(int));
    available[i] = (int*)malloc(resourceNo * sizeof(int));
    need[i] = (int*)malloc(resourceNo * sizeof(int));
  }
  available[processNo] = (int*)malloc(resourceNo * sizeof(int));
}

void deallocate(int processNo, int resourceNo)
{
  for (int i = 0; i < processNo; i++)
  {
    free(allocation[i]);
    free(available[i]);
    free(max[i]);
    free(need[i]);
  }
  free(available[processNo]);
  free(allocation);
  free(available);
  free(max);
  free(need);
  free(safeSequence);
  free(executed);
}
void inputAllocationVal(int processNo, int resourceNo)
{
  for (int i = 0; i < processNo; i++)
  {
    for (int j = 0; j < resourceNo; j++)
    {
      printf("Input instances of R%d allocated to P%d : ", j, i);
      scanf("%d", &allocation[i][j]);
    }
    executed[i] = 0;
  }

  printf("\n\n");
}

void inputMaxVal(int processNo, int resourceNo)
{
   for (int i = 0; i < processNo; i++)
  {
    for (int j = 0; j < resourceNo; j++)
    {
      printf("Input max instances of R%d allocated to P%d : ", j, i);
      scanf("%d", &max[i][j]);
    }
  }

  printf("\n\n");
}

void getNeedVal(int processNo, int resourceNo)
{
  for (int i = 0; i < processNo; i++)
  {
    for (int j = 0; j < resourceNo; j++)
    {
      need[i][j] = max[i][j] - allocation[i][j];
    }
  }
}

int check(int processNo, int resourceNo)
{
  int flag = 1;
  for (int i = 0; i < processNo; i++)
  {
    flag = 1;
    for (int j = 0; j < resourceNo; j++)
    {
      if (available[currentResourceIndex][j] < need[i][j] || executed[i] == 1)
      {
        flag = 0;
        break;
      }
    }
    if (flag == 1)
    {
      for(int k = 0; k < resourceNo; k++)
      {
        available[currentResourceIndex + 1][k] = available[currentResourceIndex][k] + need[i][k];
      }
      currentResourceIndex++;
      executed[i] = 1;
      return i;
    }
  }
  return -1;
}

void getAvailableResources(int resourceNo)
{
  for (int i = 0; i < resourceNo; i++)
  {
    printf("Enter instances of Resource%d : ", i);
    scanf("%d", &available[0][i]);
  }
}

void bankerAlgo(int processNo, int resourceNo)
{
  int res;
  for (int i = 0; i < processNo; i++)
  {
    res = check(processNo, resourceNo);
    if (res == -1)
    {
      printf("No safe sequence found \n Deadlock has occured\n");
      return;
    }
    safeSequence[curSafe++] = res;
  }
}

/*void displayAllMatrices(int processNo, int ResourceNo)
{
  for (int i = 0; i < processNo; i++)
  {
    for (int j = 0; j < ResourceNo; j++)
    {
      
    }
  }
}*/

int main()
{
  int pNo, rNo;
  printf("Enter Process No : ");
  scanf("%d", &pNo);
  printf("Enter Reosurce No : ");
  scanf("%d", &rNo);

  initialize(pNo, rNo);
  inputAllocationVal(pNo, rNo);
  inputMaxVal(pNo, rNo);
  getAvailableResources(rNo);
  getNeedVal(pNo, rNo);
  bankerAlgo(pNo, rNo);

  printf("SAFE SEQUENCE :\n"); 
  for (int i = 0; i < pNo; i++)
  {
    printf("P%d\t", safeSequence[i]);
  }
  deallocate(pNo, rNo);
  return 0;
}