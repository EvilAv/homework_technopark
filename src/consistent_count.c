#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consistent_count.h"

double* countStolbs(const char* fileName, unsigned int *r){
    Matrix* matrix = readFile(fileName);
    *r = matrix->rowLength;
    if (matrix == NULL)
        return NULL;
    
    double* result = (double*)malloc(sizeof(double) * matrix->stolbLength);
    if (result == NULL)
        return NULL;
    memset(result, 0.0, sizeof(double) * matrix->stolbLength); // fill with 0

    for (int i = 0; i < matrix->rowLength; i++){
        for (int k = 0; k < matrix->stolbLength; k++)
            result[k] += matrix->data[i][k];
    }
    if (!deleteMatrix(matrix))
        fprintf(stderr, "Matrix was deleted incorrectly\n");
    
    return result;
}