#include <stdio.h>
#include "common.h"
#include "memory.h"
#include "firstbest.h"
#include "worstcomp.h"
#include "ai.h"

void runAlgorithm(int k)
{
    if (nb == 0 || np == 0) {
        printf("Create memory blocks and processes first.\n");
        return;
    }
    if (k == 0)
        firstFit();
    else if (k == 1)
        bestFit();
    else
        worstFit();

    showAllocation(k);
    calculateMetrics(k);
}

int main()
{
    int choice;

    do {
        printf("\n===== AI-Based Memory Allocation Simulator =====\n");
        printf("1. Create Memory Blocks\n");
        printf("2. Create Processes\n");
        printf("3. Display Memory and Processes\n");
        printf("4. First Fit\n");
        printf("5. Best Fit\n");
        printf("6. Worst Fit\n");
        printf("7. Fragmentation Analysis\n");
        printf("8. Compare Algorithms\n");
        printf("9. AI Strategy Selection\n");
        printf("10. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: createMemory(); break;
        case 2: createProcess(); break;
        case 3: displayInput(); break;
        case 4: runAlgorithm(0); break;
        case 5: runAlgorithm(1); break;
        case 6: runAlgorithm(2); break;
        case 7: fragmentationAnalysis(); break;
        case 8: compareAlgorithms(); break;
        case 9: aiSelection(); break;
        case 10: printf("Bye.\n"); break;
        default: printf("Wrong choice.\n");
        }
    } while (choice != 10);

    return 0;
}
