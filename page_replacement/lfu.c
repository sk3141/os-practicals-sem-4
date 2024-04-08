#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_STRING_SIZE 100
// 3 2 1 3 4 1 6 2 4 3 4 2 1 4 5 2 1 3 4
typedef struct
{
  int holding;
  int frequency;
  int duration;
} Frame;

Frame *mainMemory;
int hits = 0, misses = 0;
int inputString[MAX_STRING_SIZE];
int frequencyArray[MAX_STRING_SIZE + 1];
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
    mainMemory[i].duration = 0;
    mainMemory[i].frequency = 0;
  }
  for (int i = 0; i < MAX_STRING_SIZE; i++)
  {
    frequencyArray[i] = 0;
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

int leastFrequent(int frameNo, int newPage)
{
  int min = 0;
  for (int i = 0; i < frameNo; i++)
  {
    if (mainMemory[i].holding == -1)
    {mainMemory[i].duration++;
      return i;
    }
    else if (frequencyArray[mainMemory[i].holding] < frequencyArray[mainMemory[min].holding]){
      mainMemory[i].duration++;
      min = i;
    }
    else if (frequencyArray[mainMemory[i].holding] == frequencyArray[mainMemory[min].holding])
    {
      mainMemory[i].duration++;
      if (mainMemory[i].duration > mainMemory[min].duration)
        min = i;
      else if (mainMemory[i].duration <= mainMemory[min].duration)
        continue;
    }
  }
  return min;
}
void lfuPageReplacement(int frameNo)
{
  int max;
  for (int i = 0; i <= count; i++)
  {
    if (checkPage(frameNo, inputString[i]) == INT_MIN)
    {
      max = leastFrequent(frameNo, inputString[i]);
      mainMemory[max].holding = inputString[i];
      frequencyArray[inputString[i]]++;
      misses++;
    }
    else
    {
      frequencyArray[inputString[i]]++;
      hits++;
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
  lfuPageReplacement(frames);
  printf("No of hits = %d\n", hits);
  printf("No of misses = %d\n", --misses);
  return 0;
}
// 7 0 2 4 3 1 4 7 2 0 4 3 0 3 2 7