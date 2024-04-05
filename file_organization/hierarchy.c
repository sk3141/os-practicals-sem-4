#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FILES 100
#define MAX_SUBDIRECTORIES 100

typedef struct {
    char fileName[50];
    char fileType[10];
    int fileSize;
} File;

typedef struct {
    char directoryName[50];
    int parentDirectory;
} Directory;

File rootDirectory[MAX_FILES];
Directory directories[MAX_SUBDIRECTORIES];
int nextFileIndex = 0;
int nextDirectoryIndex = 0;

void initializeDirectory() {
    nextFileIndex = 0;
    nextDirectoryIndex = 0;
}

void createFile(char *fileName, char *fileType, int fileSize, int parentDirectory) {
    if (nextFileIndex >= MAX_FILES) {
        printf("Error: Maximum number of files reached.\n");
        return;
    }

    strcpy(rootDirectory[nextFileIndex].fileName, fileName);
    strcpy(rootDirectory[nextFileIndex].fileType, fileType);
    rootDirectory[nextFileIndex].fileSize = fileSize;

    printf("File created successfully in directory: %s\n", directories[parentDirectory].directoryName);
    nextFileIndex++;
}

void createDirectory(char *directoryName, int parentDirectory) {
    if (nextDirectoryIndex >= MAX_SUBDIRECTORIES) {
        printf("Error: Maximum number of directories reached.\n");
        return;
    }

    strcpy(directories[nextDirectoryIndex].directoryName, directoryName);
    directories[nextDirectoryIndex].parentDirectory = parentDirectory;

    printf("Directory created successfully.\n");
    nextDirectoryIndex++;
}

void displayDirectoryContents(int directoryIndex) {
    printf("Directory: %s\n", directories[directoryIndex].directoryName);
    printf("File Name\tFile Type\tFile Size\n");
    for (int i = 0; i < nextFileIndex; i++) {
        printf("%s\t\t%s\t\t%d\n", rootDirectory[i].fileName, rootDirectory[i].fileType, rootDirectory[i].fileSize);
    }
}

int main() {
    initializeDirectory();

    int choice, fileSize, parentDirectory;
    char fileName[50], fileType[10], directoryName[50];

    do {
        printf("\nHierarchical Directory Structure\n");
        printf("1. Create File\n");
        printf("2. Create Directory\n");
        printf("3. Display Directory Contents\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter file name: ");
                scanf("%s", fileName);
                printf("Enter file type: ");
                scanf("%s", fileType);
                printf("Enter file size: ");
                scanf("%d", &fileSize);
                printf("Enter parent directory index (0 for root): ");
                scanf("%d", &parentDirectory);
                createFile(fileName, fileType, fileSize, parentDirectory);
                break;
            case 2:
                printf("Enter directory name: ");
                scanf("%s", directoryName);
                printf("Enter parent directory index (0 for root): ");
                scanf("%d", &parentDirectory);
                createDirectory(directoryName, parentDirectory);
                break;
            case 3:
                printf("Enter directory index to display contents: ");
                scanf("%d", &parentDirectory);
                displayDirectoryContents(parentDirectory);
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