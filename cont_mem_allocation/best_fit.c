#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FALSE 0
#define TRUE 1
#define MEM_CAPACITY 100
#define MAX_PROCESS 10

typedef struct {
  int pid;
  int memoryRequired;
  int startingPos;
} Process;

int mainMemory[MEM_CAPACITY];
Process processList[MAX_PROCESS];
int nextPid = 0;

void initializeMemory() 
{
  for (int i = 0; i < MEM_CAPACITY; i++)
  {
    mainMemory[i] == FALSE;
  }
}
int getHoleLength(int start)
{
  int spaceCount = 0;
  for (int i = start; mainMemory[i] != TRUE && i < MEM_CAPACITY; i++)
    spaceCount++;

  return spaceCount;
}

void bestAllocate(int pMem)
{
  Process newProcess;
  newProcess.pid = nextPid;
  newProcess.memoryRequired = pMem;
  int minHoleLength = INT_MAX;
  int holeStart = 0;
  for (int i = 0; i < MEM_CAPACITY; i++)
  {
    if (mainMemory[i] == FALSE)
    {
      if (getHoleLength(i) < minHoleLength && getHoleLength(i) >= pMem)
      {
        minHoleLength = getHoleLength(i);
        holeStart = i;
      }
    }
  }
  if (minHoleLength < pMem)
  {
    printf("Cannot allocate process : space not found\n");
    return;
  }
  for (int i = holeStart; i < holeStart + pMem; i++)
  {
    mainMemory[i] = TRUE;
  }

  newProcess.startingPos = holeStart;
  processList[nextPid++] = newProcess;
  printf("Process Allocated\n");
  return;
}

void displayMemory()
{
  for (int i = 0; i < nextPid; i++)
  {
    printf("P%d\t%d-%d\n",
     i, processList[i].startingPos, (processList[i].startingPos + processList[i].memoryRequired));
  }
}

void deallocate(int pid)
{
  for (int i = 0; i < nextPid; i++)
  {
    if (processList[i].pid == pid)
    {
      for (int j = processList[i].startingPos; j < processList[i].startingPos + processList[i].memoryRequired; j++)
      {
        mainMemory[j] = FALSE;
      }
      processList[i].memoryRequired = 0;
      processList[i].startingPos = 0;
      return;
    }
  }
  printf("Process not found \n");
  return;
}

int main()
{
  int choice;
  int mem;
  int pid;
  initializeMemory();
  printf("BEST FIT MEMORY ALLOCATION \n\n");

  while (TRUE)
  {
    printf("Enter choice : 1. allocate\t2. deallocate\t3. display\t4. Exit\n Choice : ");
    scanf("%d", &choice);

    switch (choice)
    {
      case 1:
      {
        printf("Enter memory : ");
        scanf("%d", &mem);
        bestAllocate(mem);
        printf("Process Allocated with process id %d\n", nextPid - 1);
        break;
      }

      case 2:
      {
        printf("Enter pid : ");
        scanf("%d", &pid);
        deallocate(pid);
        break;
      }

      case 3:
      {
        displayMemory();
        break;
      }
      case 4:
      {
        printf("Program terminated\n");
        return 0;
      }
      default:
      {
        printf("invalid input\nProgram terminated\n");
        return 0;
      }
    }
  }
  return 0;
}