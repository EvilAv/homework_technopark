#ifndef PARALLEL_COUNT_H
#define PARALLEL_COUNT_H
#include "matrix.h"

typedef struct procInfo{
    unsigned int rowsInProc;
    unsigned int id;
    unsigned int totalAmount;
    unsigned int rowsInLastProc;
} procInfo;

double* countStolbs(const char* fileName, unsigned int *row);
unsigned int rowsInCurProc(procInfo p);

#endif