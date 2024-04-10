#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_STRING_SIZE 100
// 3 2 1 3 4 1 6 2 4 3 4 2 1 4 5 2 1 3 4
typedef struct
{
  int holding;
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

int leastFrequentPage(int frameNo)
{
  int index1, index2, minFrequencyIndex;
  minFrequencyIndex = 0;

  for (int i = 0; i < frameNo; i++)
  {
    index1 = mainMemory[i].holding;
    index2 = mainMemory[minFrequencyIndex].holding;
    if (mainMemory[i].holding == -1)
    {
      minFrequencyIndex = i;
      return minFrequencyIndex;
    }
    else if (frequencyArray[index1] < frequencyArray[index2])
      minFrequencyIndex = i;
    else if (frequencyArray[index1] == frequencyArray[index2])
    {
      if (mainMemory[i].duration > mainMemory[minFrequencyIndex].duration)
        minFrequencyIndex = i;
    }
  }
  return minFrequencyIndex;
}

void updateDuration(int frameNo)
{
  for (int  i = 0; i < frameNo; i++)
  {
    if (mainMemory[i].holding != -1)
      mainMemory[i].duration++;
  }
}

void logp(int frameNo)
{
  for (int i = 0; i < frameNo; i++)
  {
    printf("%d", mainMemory[i].holding);
  }
  printf("\n");
}
void lfuPageReplacement(int frameNo)
{
  int res;
  for (int i = 0; i < count; i++)
  {
    int curPage = inputString[i];
    if (checkPage(frameNo, curPage) == INT_MIN)
    {
      misses++;
      res = leastFrequentPage(frameNo);
      mainMemory[res].holding = curPage;
      mainMemory[res].duration = 0;
      frequencyArray[inputString[i]]++;
      updateDuration(frameNo);
      printf("M");
      logp(frameNo);
      continue;
    }
    hits++;
    frequencyArray[inputString[i]]++;
    updateDuration(frameNo);
    printf("H");
    logp(frameNo);
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
  printf("No of misses = %d\n", misses);
  return 0;
}
// 7 0 2 4 3 1 4 7 2 0 4 3 0 3 2 7