#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1
#define MAX_FILES 100
#define MAX_BLOCKS 1000

typedef struct 
{
  int filled;
  int nextBlock;
} DiskBlock;

typedef struct 
{
  int fileID;
  int fileLength;
  int startingPos;
  char fileName[50];
} File;

int nextFileID = 0;
File fileList[MAX_FILES];
DiskBlock disk[MAX_BLOCKS];

void inititalize()
{
  for (int i = 0; i < MAX_BLOCKS; i++) { disk[i].filled = FALSE; }
}

void allocate(char* fileName, int start, int fileLength)
{
  if (fileLength >= MAX_BLOCKS)
  {
    printf("Cannot create file : size too big\n\n" );
    return;
  }

  if (nextFileID >= MAX_FILES)
  {
    printf("Cannot create File : limit reached");
    return;
  }

  if (disk[start].filled != FALSE)
  {
    printf("Cannot allocate file with given starting position\n\n");
    return;
  }

  File newFile;
  newFile.fileID = nextFileID;
  newFile.fileLength = fileLength;
  newFile.startingPos = start;
  strcpy(newFile.fileName, fileName);
  int counter = fileLength;
  int lastBlock = -1;
  for (int i = start; counter > 0; i++)
  {
    if (lastBlock == -1)
    {
      disk[i].filled = TRUE;
      lastBlock = i;
      counter--;
      continue;
    }

    if (disk[i].filled == FALSE)
    {
      disk[i].filled = TRUE;
      disk[lastBlock].nextBlock = i;
      lastBlock = i;
      counter--;
      continue;
    } 
  }
  disk[lastBlock].nextBlock = -1;
  fileList[nextFileID++] = newFile;
}

void fileLookup(char* fileName)
{
  for (int i = 0; i <= nextFileID; i++)
  {
    if (strcmp(fileList[i].fileName, fileName) == 0)
    {
      printf("String Found\n");
      printf("Blocks occupied\n");
      int j = fileList[i].startingPos;
      do {
        printf("%d\t", j);
        j = disk[j].nextBlock;
      }
      while (disk[j].nextBlock != -1);
      printf("%d\t", j);
      printf("\n");
      return;
    }
  }
  printf("File not found\n");
}

int main()
{
  inititalize();
  char fileName[50];
  int fileLength, start, choice;
  printf("Indexed File Allocation\n\n");
  while (TRUE)
  {
    printf("Choice : 1. Insert file\t 2. Lookup File\t 3.Exit\n\n");
    scanf("%d", &choice);
    switch (choice)
    {
      case 1:
      {
        printf("Enter file name :- ");
        scanf("%s", &fileName);
        printf("Enter file length :- ");
        scanf("%d", &fileLength);
        printf("Enter file starting position in disk :- ");
        scanf("%d", &start);
        allocate(fileName, start, fileLength);
        break;
      }

      case 2:
      {
        printf("Enter file name :- ");
        scanf("%s", &fileName);
        fileLookup(fileName);
        break;
      }
      case 3:
      {
        printf("Program terminated\n");
        return 0;
      }

      default:
      printf("Invalid choice. Please try again.\n");
      break;
    }
  }
}
