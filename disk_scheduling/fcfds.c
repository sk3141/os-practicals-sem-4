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

void fcfsDiskScheduling() {
    int totalMovement = 0;

    for (int i = 0; i < totalRequests; i++) {
        int movement = abs(headPosition - requests[i]);

        printf("Move from %d to %d with a movement of %d\n", headPosition, requests[i], movement);
        totalMovement += movement;

        headPosition = requests[i];
    }

    printf("Total head movement = %d\n", totalMovement);
}

int main() {
    getInputRequests();

    printf("Enter the initial head position: ");
    scanf("%d", &headPosition);

    fcfsDiskScheduling();

    return 0;
}