#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_BLOCKS 1000
#define MAX_FILES 100

typedef struct
{
  int fileID;
  int indexBlockID;
  int fileLength;
  char fileName[50];
} File;

typedef struct 
{
  int BlockID;
  int blockList[MAX_BLOCKS];
  int numberOfBlocks;
} IndexBlock;

File fileList[MAX_FILES];
IndexBlock indexBlockList[MAX_FILES];
int nextIndexBlock = 0;
int nextFileID = 0;
int disk[MAX_BLOCKS];

void initialize()
{
  for (int i = 0; i < MAX_BLOCKS; i++) { disk[i] = FALSE; }
  for (int i = 0; i < MAX_FILES; i++)
  {
    for (int j = 0; j < MAX_BLOCKS; j++)
    {
      indexBlockList[i].blockList[j] = -1;
    }
  }
}
int createFile(char* fileName, int fileLength)
{
  if (fileLength > MAX_BLOCKS)
  {
    printf("Cannot create file : file size too big\n\n");
    return -1;
  }

  if (nextFileID >= MAX_FILES)
  {
    printf("Cannot create any more files : Limit reached\n\n");
    return -1;
  }

  File newFile;
  newFile.fileID = nextFileID++;
  newFile.fileLength = fileLength;
  newFile.indexBlockID = nextIndexBlock;
  strcpy(newFile.fileName, fileName);

  for (int i = 0; i < fileLength; i++)
  {
    indexBlockList[nextIndexBlock].blockList[i] = nextIndexBlock + i + 1;
  }
  fileList[nextFileID] = newFile;
  indexBlockList[nextIndexBlock].numberOfBlocks = fileLength;
  nextIndexBlock += fileLength;

  return newFile.fileID;
}

void displayFiles() {
    printf("File ID\tFile Name\tSize\tIndex Block ID\n");
    for (int i = 0; i < nextFileID; i++) {
        printf("%d\t%s\t\t%d\t%d\n", fileList[i].fileID, fileList[i].fileName, fileList[i].fileLength, fileList[i].indexBlockID);
    }
}

void displayIndexBlock(int indexBlockID) {
    printf("Index Block ID: %d\n", indexBlockID);
    printf("Block Pointers:\n");
    for (int i = 0; i < indexBlockList[indexBlockID].numberOfBlocks; i++) {
        printf("%d -> %d\n", i, indexBlockList[indexBlockID].blockList[i]);
    }
}

int main() {
    initializeIndexBlocks();

    int choice, fileSize, fileID;
    char fileName[50];

    do {
        printf("\nIndexed File Allocation Simulation\n");
        printf("1. Create File\n");
        printf("2. Display Files\n");
        printf("3. Display Index Block\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fileName);
                printf("Enter file size (number of blocks): ");
                scanf("%d", &fileSize);
                fileID = createFile(fileName, fileSize);
                if (fileID != -1) {
                    printf("File created successfully. File ID: %d\n", fileID);
                }
                break;
            case 2:
                displayFiles();
                break;
            case 3:
                printf("Enter index block ID: ");
                scanf("%d", &fileID);
                displayIndexBlock(fileID);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}