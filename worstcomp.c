#include <stdio.h>
#include "common.h"
#include "memory.h"
#include "worstcomp.h"

void worstFit()
{
    int i, j, worst;
    prepareCopy(2);

    for (i = 0; i < np; i++) {
        worst = -1;
        for (j = 0; j < nb; j++) {
            if (remaining[2][j] >= processSize[i]) {
                if (worst == -1 || remaining[2][j] > remaining[2][worst])
                    worst = j;
            }
        }
        if (worst != -1) {
            allocation[2][i] = worst;
            remaining[2][worst] = remaining[2][worst] - processSize[i];
        }
    }
}

void calculateMetrics(int k)
{
    int i, j;
    int used[MAX];
    int allocatedMem = 0;

    res[k].allocated = 0;
    res[k].unallocated = 0;
    res[k].internal = 0;
    res[k].external = 0;

    for (j = 0; j < nb; j++)
        used[j] = 0;

    for (i = 0; i < np; i++) {
        if (allocation[k][i] != -1) {
            res[k].allocated++;
            allocatedMem = allocatedMem + processSize[i];
            used[allocation[k][i]] = 1;
        } else
            res[k].unallocated++;
    }

    for (j = 0; j < nb; j++) {
        if (used[j] == 1)
            res[k].internal += remaining[k][j];
        else if (res[k].unallocated > 0)
            res[k].external += remaining[k][j];
    }

    res[k].efficiency = allocatedMem * 100.0 / totalMemory();
    res[k].done = 1;
}

int allDone()
{
    int i;
    for (i = 0; i < 3; i++) {
        if (res[i].done == 0) {
            printf("Run First Fit, Best Fit and Worst Fit first.\n");
            return 0;
        }
    }
    return 1;
}

void compareAlgorithms()
{
    int i, best = 0;

    if (!allDone())
        return;

    printf("\nMetric\t\t\tFirst\tBest\tWorst\n");
    printf("Allocated\t\t");
    for (i = 0; i < 3; i++) printf("%d\t", res[i].allocated);
    printf("\nUnallocated\t\t");
    for (i = 0; i < 3; i++) printf("%d\t", res[i].unallocated);
    printf("\nUnused memory\t\t");
    for (i = 0; i < 3; i++) printf("%d\t", res[i].internal + res[i].external);
    printf("\nEfficiency %%\t\t");
    for (i = 0; i < 3; i++) printf("%.2f\t", res[i].efficiency);
    printf("\n");

    for (i = 1; i < 3; i++)
        if (res[i].efficiency > res[best].efficiency)
            best = i;
    printf("Highest efficiency: %s\n", names[best]);
}

void fragmentationAnalysis()
{
    int i;

    if (!allDone())
        return;

    printf("\nAlgorithm\tInternal\tExternal\tTotal %%\n");
    for (i = 0; i < 3; i++) {
        printf("%s\t%d\t\t%d\t\t%.2f\n", names[i], res[i].internal,
               res[i].external,
               (res[i].internal + res[i].external) * 100.0 / totalMemory());
    }
}
