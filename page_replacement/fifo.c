#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_STRING_SIZE 100

typedef struct
{
  int holding;
  int holdingDuration;
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
    mainMemory[i].holdingDuration = 0;
  }
}

int checkPage(int frameNo, int nextPage)
{
  for (int i = 0; i < frameNo; i++)
  {
    if (mainMemory[i].holding == nextPage)
      return 1;
  }
  return 0;
}

int longestDuration(int frameNo)
{
  int maxIndex = 0;
  for (int i = 0; i < frameNo; i++)
  {
    mainMemory[i].holdingDuration++;
    if (mainMemory[i].holdingDuration > mainMemory[maxIndex].holdingDuration){
      maxIndex = i;
    }
  }
  return maxIndex;
}
void fifoPageReplacement(int frameNo)
{
  int max;
  for (int i = 0; i <= count; i++)
  {
    if (checkPage(frameNo, inputString[i]) != 1)
    {
      max = longestDuration(frameNo);
      mainMemory[max].holding = inputString[i];
      mainMemory[max].holdingDuration = 0;
      misses++;
    }
    else
      hits++;
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
  fifoPageReplacement(frames);
  printf("No of hits = %d\n", hits);
  printf("No of misses = %d\n", --misses);
  return 0;
}