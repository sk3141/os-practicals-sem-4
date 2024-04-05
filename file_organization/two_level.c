#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FILES 100
#define MAX_DIR 100

typedef struct
{
  char fileName[50];
  char fileType[50];
  int fileSize; 
} File;

typedef struct 
{ 
  int uid;
  char userName[50];
  File fileList[MAX_FILES];
  int nextIndex; 
} Directory;

int nextUID = 0;
Directory rootDirectory[MAX_DIR];

void createUserDir(char* userName)
{
  Directory newUser;
  strcpy(newUser.userName, userName);
  newUser.nextIndex = 0;
  newUser.uid = nextUID;
  rootDirectory[nextUID++] = newUser; 
}

int check(char* fileName, char* fileType, int uid)
{
  for (int i = 0; i < rootDirectory[uid].nextIndex; i++)
  {
    if (strcmp(rootDirectory[uid].fileList[i].fileName, fileName) == 0
      && strcmp(rootDirectory[uid].fileList[i].fileType, fileType) == 0)
    {
      return 1;
    }
  }
  return 0;
}

void createFile(char* fileName, char* fileType, int fileSize, int uid)
{
  File newFile;
  strcpy(newFile.fileName, fileName);
  strcpy(newFile.fileType, fileType);
  newFile.fileSize = fileSize;
  rootDirectory[uid].fileList[rootDirectory[uid].nextIndex++] = newFile;
}

void displayDirectory(int uid)
{
  if (rootDirectory[uid].nextIndex == 0)
  {
    printf("Empty directory\n");
    return;
  }

  printf("Directory Contents\n");
  printf("%s%50s%50s\n", "File Name", "File Type", "File Size");
  for (int i = 0; i < rootDirectory[uid].nextIndex; i++)
  {
    printf("%s%50s%50d\n", 
      rootDirectory[uid].fileList[i].fileName, 
      rootDirectory[uid].fileList[i].fileType, 
      rootDirectory[uid].fileList[i].fileSize);
  }
}

int main()
{
  char fileName[50];
  char fileType[50];
  int fileSize;
  char userName[50];
  int uid;
  int choice;
  printf("Two level directory simulation \n\n");
  
  while(1)
  {
    printf("Enter choice : 1. New File 2. Display Directory 3. New User 4. Exit\n Choice : ");
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
        printf("Enter uid : ");
        scanf("%d", &uid);

        if (check(fileName, fileType, uid) == 1)
        {
          printf("Cannot create file : already exists");
          break;
        }
        createFile(fileName, fileType, fileSize, uid);
        break;
      }

      case 2:
      {
        printf("Enter uid : ");
        scanf("%d", &uid);
        displayDirectory(uid);
        break;
      }

      case 3:
      {
        printf("Enter user name : ");
        scanf("%s", userName);
        createUserDir(userName);
        break;
      }
      case 4:
      {
        printf("Program terminated\n");
        return 0;
      }
      
      default:
      {
        printf("Invalud choice \n Program terminated\n");
        return 0;
      }
    }
  }
}