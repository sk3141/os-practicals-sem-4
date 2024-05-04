#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_FILES 100

typedef struct 
{
  char fileName[100];
  char fileType[10];
  int fileSize;
} File;

File directory[MAX_FILES];
int nextFileIndex = 0;

int check(char* fileName, char* fileType)
{
  for (int i = 0; i < nextFileIndex; i++)
  {
    if (strcmp(directory[i].fileName, fileName) == 0
      && strcmp(directory[i].fileType, fileType) == 0)
    {
      return 1;
    }
  }
  return 0;
}
void createFile(char* fileName, char* fileType, int fileSize)
{
  if (nextFileIndex == MAX_FILES)
  {
    printf("Cannot create file : file limit reached \n");
    return;
  }

  File newFile;
  strcpy(newFile.fileName, fileName);
  strcpy(newFile.fileType, fileType);
  newFile.fileSize = fileSize;

  directory[nextFileIndex++] = newFile;
}

void displayDirectory()
{
  if (nextFileIndex == 0)
  {
    printf("Empty directory\n");
    return;
  }

  printf("Directory Contents\n");
  printf("%-40s%-40s%-40s\n", "File Name", "File Type", "File Size");
  for (int i = 0; i < nextFileIndex; i++)
  {
    printf("%-40s%-40s%-40d\n", directory[i].fileName, directory[i].fileType, directory[i].fileSize);
  }
}

int main()
{
  char fileName[50];
  char fileType[50];
  int fileSize;
  int choice;
  printf("Single level directory simulation \n\n");
  
  while(1)
  {
    printf("Enter choice : 1. New File 2. Display Directory 3. Exit\n Choice : ");
    scanf("%d", &choice);

    switch (choice)
    {
      case 1:
      {
        printf("Enter File Name : ");
        scanf("%s", &fileName);
        printf("Enter File Type : ");
        scanf("%s", &fileType);
        printf("Enter file Size : ");
        scanf("%d", &fileSize);
        if (check(fileName, fileType) == 1)
        {
          printf("Cannot create file : already exists");
          break;
        }
        createFile(fileName, fileType, fileSize);
        break;
      }

      case 2:
      {
        displayDirectory();
        break;
      }

      case 3:
      {
        printf("Program terminated\n");
        return 0;
      }
      
      default:
      {
        printf("Invalid choice \n Program terminated\n");
        return 0;
      }
    }
  }
}
