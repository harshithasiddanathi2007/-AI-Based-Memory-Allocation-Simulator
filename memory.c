#include <stdio.h>
#include "common.h"
#include "memory.h"

int blockSize[MAX];
int processSize[MAX];
int nb = 0, np = 0;
int allocation[3][MAX];
int remaining[3][MAX];
struct result res[3];
char names[3][12] = {"First Fit", "Best Fit", "Worst Fit"};

void clearResults()
{
    int i;
    for (i = 0; i < 3; i++)
        res[i].done = 0;
}

void createMemory()
{
    int i;
    do {
        printf("Number of memory blocks (1-%d): ", MAX);
        scanf("%d", &nb);
    } while (nb < 1 || nb > MAX);

    for (i = 0; i < nb; i++) {
        do {
            printf("Size of block %d: ", i + 1);
            scanf("%d", &blockSize[i]);
        } while (blockSize[i] <= 0);
    }
    clearResults();
}

void createProcess()
{
    int i;
    do {
        printf("Number of processes (1-%d): ", MAX);
        scanf("%d", &np);
    } while (np < 1 || np > MAX);

    for (i = 0; i < np; i++) {
        do {
            printf("Size of process %d: ", i + 1);
            scanf("%d", &processSize[i]);
        } while (processSize[i] <= 0);
    }
    clearResults();
}

void displayInput()
{
    int i;
    printf("\nBlock\tSize\n");
    for (i = 0; i < nb; i++)
        printf("%d\t%d\n", i + 1, blockSize[i]);
    printf("\nProcess\tSize\n");
    for (i = 0; i < np; i++)
        printf("%d\t%d\n", i + 1, processSize[i]);
}

/* gives algorithm k a fresh copy of the blocks */
void prepareCopy(int k)
{
    int i;
    for (i = 0; i < nb; i++)
        remaining[k][i] = blockSize[i];
    for (i = 0; i < np; i++)
        allocation[k][i] = -1;
}

int totalMemory()
{
    int i, t = 0;
    for (i = 0; i < nb; i++)
        t = t + blockSize[i];
    return t;
}
