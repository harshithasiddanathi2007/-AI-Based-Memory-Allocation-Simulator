#include <stdio.h>
#include "common.h"
#include "memory.h"
#include "worstcomp.h"
#include "ai.h"

void aiSelection()
{
    int i, j, best = 0;
    int totalP = 0, bigP = 0, bigB = 0;
    float fill, ratio, frag, alloc;
    float wa, we, wf, score, bestScore = -1;

    if (!allDone())
        return;

    for (i = 0; i < np; i++) {
        totalP = totalP + processSize[i];
        if (processSize[i] > bigP)
            bigP = processSize[i];
    }
    for (j = 0; j < nb; j++)
        if (blockSize[j] > bigB)
            bigB = blockSize[j];

    fill = totalP * 100.0 / totalMemory();   /* memory load */
    ratio = bigP * 100.0 / bigB;             /* largest process vs largest block */

    printf("\nFeature 1: memory load = %.2f%%\n", fill);
    printf("Feature 2: largest process / largest block = %.2f%%\n", ratio);

    if (fill > 80.0 || ratio > 60.0) {
        printf("Input type: TIGHT (allocation success matters most)\n");
        wa = 60; we = 25; wf = 15;
    } else {
        printf("Input type: RELAXED (low fragmentation matters more)\n");
        wa = 30; we = 30; wf = 40;
    }

    for (i = 0; i < 3; i++) {
        frag = (res[i].internal + res[i].external) * 100.0 / totalMemory();
        alloc = res[i].allocated * 100.0 / np;
        score = (wa * alloc + we * res[i].efficiency + wf * (100 - frag)) / 100;
        printf("%s Score: %.2f\n", names[i], score);
        if (score > bestScore) {   /* ties go to the earlier strategy */
            bestScore = score;
            best = i;
        }
    }

    if (bestScore == 0)
        printf("No strategy could allocate anything for this input.\n");
    printf("AI-recommended strategy: %s\n", names[best]);
}
