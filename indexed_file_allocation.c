#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAX_FILE_SIZE 1000
#define MAX_FILES 100

typedef struct 
{
    char fileName[50];
    int fileLength;
} File;

typedef struct
{
    int fileBlocks[MAX_FILE_SIZE];
    int id;
} IndexBlock;
