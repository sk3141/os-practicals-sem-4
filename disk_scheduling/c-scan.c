#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

int requests[MAX_REQUESTS];
int headPosition;
int totalRequests;

void getInputRequests() {
    printf("Enter the total number of requests: ");
    scanf("%d", &totalRequests);

    printf("Enter the requests (head position + requests): \n");
    for (int i = 0; i < totalRequests; i++) {
        scanf("%d", &requests[i]);
    }
}

void cScanDiskScheduling() {
    int totalMovement = 0;
    int currentRequestIndex = 0;

    for (int i = 0; i < totalRequests - 1; i++) {
        for (int j = 0; j < totalRequests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    while (currentRequestIndex < totalRequests && requests[currentRequestIndex] < headPosition) {
        currentRequestIndex++;
    }
    for (int i = currentRequestIndex; i < totalRequests; i++) {
        printf("Move from %d to %d\n", headPosition, requests[i]);
        totalMovement += abs(headPosition - requests[i]);
        headPosition = requests[i];
    }

    printf("Move from %d to %d\n", headPosition, 0);
    totalMovement += headPosition;
    headPosition = 0;

    for (int i = 0; i < currentRequestIndex; i++) {
        printf("Move from %d to %d\n", headPosition, requests[i]);
        totalMovement += abs(headPosition - requests[i]);
        headPosition = requests[i];
    }

    printf("Total head movement = %d\n", totalMovement);
}

int main() {
    getInputRequests();

    printf("Enter the initial head position: ");
    scanf("%d", &headPosition);

    cScanDiskScheduling();

    return 0;
}