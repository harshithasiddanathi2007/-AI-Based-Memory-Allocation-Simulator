#include <stdio.h>
#include "common.h"
#include "memory.h"
#include "firstbest.h"

void firstFit()
{
    int i, j;
    prepareCopy(0);

    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (remaining[0][j] >= processSize[i]) {
                allocation[0][i] = j;
                remaining[0][j] = remaining[0][j] - processSize[i];
                break;   /* first suitable block, stop looking */
            }
        }
    }
}

void bestFit()
{
    int i, j, best;
    prepareCopy(1);

    for (i = 0; i < np; i++) {
        best = -1;
        for (j = 0; j < nb; j++) {
            if (remaining[1][j] >= processSize[i]) {
                if (best == -1 || remaining[1][j] < remaining[1][best])
                    best = j;
            }
        }
        if (best != -1) {
            allocation[1][i] = best;
            remaining[1][best] = remaining[1][best] - processSize[i];
        }
    }
}

void showAllocation(int k)
{
    int i, b;

    printf("\n--- %s ---\n", names[k]);
    printf("Process\tSize\tBlock\tBlock space left\n");
    for (i = 0; i < np; i++) {
        b = allocation[k][i];
        printf("%d\t%d\t", i + 1, processSize[i]);
        if (b == -1)
            printf("NOT ALLOCATED\t-\n");
        else
            printf("%d\t%d\n", b + 1, remaining[k][b]);
    }

    printf("\nBlock\tSize\tRemaining\n");
    for (i = 0; i < nb; i++)
        printf("%d\t%d\t%d\n", i + 1, blockSize[i], remaining[k][i]);

    for (i = 0; i < np; i++)
        if (allocation[k][i] == -1)
            printf("Process %d (size %d) could not be allocated.\n",
                   i + 1, processSize[i]);
}
