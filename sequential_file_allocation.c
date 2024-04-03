#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

int sequentialAllocation(int startingPos, int fileLength, int diskCapacity, int diskBlocks[])
{
  int i; // Looping variable
  // Checking if file length is less than disk capacity
  if (diskCapacity < startingPos + fileLength + 1) { return FALSE; }

  // Checking if blocks are available for allocation from starting position
  for (i = startingPos - 1; i < (startingPos + fileLength - 1); i++)
  {
    if (diskBlocks[i] == TRUE)
    {
      return FALSE;
    }
  }

  // Allocating file in disk
  for (i = startingPos - 1; i < (startingPos + fileLength - 1); i++)
  {
    diskBlocks[i] = TRUE;
  }
  return TRUE;
}

int main()
{
  int diskCapacity, fileLength, startingPos;
  int i, j; //Looping Variables
  int choice;

  printf("Sequential File Allocation Simulation \n\n");
  printf("Enter disk Capacity :- ");
  scanf("%d", &diskCapacity);
  printf("\n\n");
  int disk[diskCapacity];

  //Initializing disk
  for (i = 0; i < diskCapacity; i++)
  {
    disk[i] = FALSE;
  }

  while (TRUE)
  {
    printf("Enter choice :- 1. Allocate File\t2. Exit\nChoice:= ");
    scanf("%d", &choice);
    if (choice == 2)
    {
      printf("Program terminated");
      return 0;
    }

    printf("Enter starting position of file :- ");
    scanf("%d", &startingPos);
    printf("Enter file length :- ");
    scanf("%d", &fileLength);

    if (sequentialAllocation(startingPos, fileLength, diskCapacity, disk))
    {
      printf("File Allocated successfully\n\n");
    }
    else 
    {
      printf("Could not allocate file\n\n");
    }
  }
}