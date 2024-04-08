#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_STRING_SIZE 100

typedef struct 
{
  int holdingPage;
  int holdingDuration;
} Frame;

int frequencyArray[MAX_STRING_SIZE + 1];
Frame mainMemory[MAX_STRING_SIZE];
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
  for (int i = 0; i < frameNo; i++)
  {
    mainMemory[i].holdingPage = -1;
    mainMemory[i].holdingDuration = 0;
  }
  for (int i = 0; i < MAX_STRING_SIZE; i++)
    frequencyArray[i] = 0;
}

int checkIfExists(int frameNo, int nextPage)
{
  for (int i = 0; i < frameNo; i++)
  {
    if (mainMemory[i].holdingPage == nextPage)
      return 1;
  }
  return 0;
}

int findReplacementPage(int frameNo)
{
  int replacementIndex = 0;
  for (int i = 0; i < frameNo; i++)
  {
    if (mainMemory[i].holdingPage == -1)
      return i;
    else if (frequencyArray[mainMemory[i].holdingPage] < frequencyArray[mainMemory[replacementIndex].holdingPage])
      replacementIndex = i;
    else if (frequencyArray[mainMemory[i].holdingPage] == frequencyArray[mainMemory[replacementIndex].holdingPage])
    {
      if (mainMemory[i].holdingDuration > mainMemory[replacementIndex].holdingDuration)
        replacementIndex = i;
    }
  }
  return replacementIndex;
}

void updateDuration(int frameNo, int ind)
{
  for (int i = 0; i < frameNo; i++)
  {
    if (mainMemory[i].holdingPage != -1)
      mainMemory[i].holdingDuration++;
  }
  if (ind == INT_MIN)
  {
    
  }
}

void LFUPageReplacement(int frameNo)
{
  int res;
  for (int i = 0; i <= count; i++)
  {
    if (checkIfExists(frameNo, inputString[i]) == 0)
    {
      res = findReplacementPage(frameNo);
      mainMemory[res].holdingPage = inputString[i];
      frequencyArray[inputString[i]]++;
      updateDuration(frameNo, res);
      misses++;
    }
    else
    {
      hits++;
      updateDuration(frameNo);
    }
  }
}

int main()
{
  int frameNo;
  printf("LFU PAGE REPLACEMENT ALGORITHM\n Enter an input string : ");
  getInputString();
  printf("Enter number of frames : ");
  scanf("%d", &frameNo);
  initialize(frameNo);
  LFUPageReplacement(frameNo);
  printf("No of hits = %d\n", hits);
  printf("No of misses = %d\n", --misses);
  return 0;
}
// 7 0 2 4 3 1 4 7 2 0 4 3 0 3 2 7