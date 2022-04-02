#ifndef MATRIX_H
#define MATRIX_H

#define TRUE 1
#define FALSE 0

typedef struct Matrix {
    unsigned int stolbLength;
    unsigned int rowLength;

    double** data;
} Matrix;

Matrix* createMatrix(unsigned int stolb, unsigned int row);
char deleteMatrix(Matrix* matrix);
Matrix* readFile(const char* fileName);
Matrix* splitByRows(Matrix* matrix, unsigned int startRow, unsigned int length);

#endif