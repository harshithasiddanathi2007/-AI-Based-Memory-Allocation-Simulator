#ifndef COMMON_H
#define COMMON_H

#define MAX 20

struct result {
    int allocated;
    int unallocated;
    int internal;
    int external;
    float efficiency;
    int done;
};

extern int blockSize[MAX];
extern int processSize[MAX];
extern int nb, np;
extern int allocation[3][MAX];   /* row 0 First, 1 Best, 2 Worst */
extern int remaining[3][MAX];
extern struct result res[3];
extern char names[3][12];

#endif
