#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_STRING_SIZE 100
// 3 2 1 3 4 1 6 2 4 3 4 2 1 4 5 2 1 3 4
typedef struct
{
  int holding;
  int sinceUsed;
} Frame;

Frame *mainMemory;
int hits = 0, misses = 0;
int inputString[MAX_STRING_SIZE];
int count = 0;

void getInputString()
{
  do {
    scanf("%d", &inputString[count++]);

  }
  while (getchar() != '\n' && count < 100);
}

void initialize(int frameNo)
{
  mainMemory = (Frame*)malloc(frameNo * sizeof(Frame));
  for (int i = 0; i < frameNo; i++)
  {
    mainMemory[i].holding = -1;
    mainMemory[i].sinceUsed = 0;
  }
}

int checkPage(int frameNo, int nextPage)
{
  for (int i = 0; i < frameNo; i++)
  {
    if (mainMemory[i].holding == nextPage)
      return i;
  }
  return INT_MIN;
}

int leastRecent(int frameNo)
{
  int min = 0;
  for (int i = 0; i < frameNo; i++)
  {
    if (mainMemory[i].holding == -1)
    {
      return i;
    }
    else if (mainMemory[i].sinceUsed > mainMemory[min].sinceUsed){
      min = i;
    }
  }
  return min;
}
void lruPageReplacement(int frameNo)
{
  int max;
  for (int i = 0; i <= count; i++)
  {
    if (checkPage(frameNo, inputString[i]) == INT_MIN)
    {
      max = leastRecent(frameNo);
      mainMemory[max].holding = inputString[i];
      mainMemory[max].sinceUsed = 0;
      misses++;
    }
    else
    {
      mainMemory[checkPage(frameNo, inputString[i])].sinceUsed = 0;
      hits++;
    }
    for (int j = 0; j < frameNo; j++)
    {
      if (mainMemory[j].holding != -1)
        mainMemory[j].sinceUsed++;
    }
  }
}

int main()
{
  int frames;
  printf("Enter an input string (values seperated by spaces) : ");
  getInputString();
  printf("Enter number of frames : ");
  scanf("%d", &frames);
  initialize(frames);
  lruPageReplacement(frames);
  printf("No of hits = %d\n", hits);
  printf("No of misses = %d\n", --misses);
  return 0;
}