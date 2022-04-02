#include "matrix.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

Matrix* createMatrix(unsigned int row, unsigned int stolb){
    Matrix* matrix = (Matrix*)malloc(sizeof(Matrix));
    if(matrix == NULL)
        return NULL;
    if (row == 0 || stolb ==0)
        return NULL;

    matrix->rowLength = row;
    

    matrix->data = (double**)malloc(row * sizeof(double*));

    if (matrix->data == NULL)
        return NULL;

    matrix->stolbLength = stolb;

    for (int i = 0; i < matrix->stolbLength; i++){
        matrix->data[i] = (double*)malloc(stolb * sizeof(double));
        
        if (matrix->data[i] == NULL)
            return NULL;
    }

    return matrix;
}

char deleteMatrix(Matrix* matrix){
    if (matrix == NULL)
        return FALSE;
    
    if (matrix->data == NULL){
        free(matrix);
        return FALSE;
    }

    char isOK = TRUE;

    for (int i = 0; i< matrix->stolbLength; i++){
        if (matrix->data[i] != NULL)
            free(matrix->data[i]);
        else
            isOK = FALSE;
    }
    free(matrix->data);
    free(matrix);
    return isOK;
}

Matrix* readFile(const char* fileName){
    if (fileName == NULL){
        fprintf(stderr, "Incorrect file name\n");
        return NULL;
    }

    FILE *f = fopen(fileName, "rb");
    

    if (f == NULL){
        fprintf(stderr, "Failed to open file\n");
        return NULL;
    }

    // file structure looks like: N, M, elements of matrix N*M
    unsigned int rows, stolbs;

    if (fread(&rows, sizeof(unsigned int), 1, f) == 0){
        fprintf(stderr, "Failed to get matrix size\n");
        return NULL;
    }
    if (fread(&stolbs, sizeof(unsigned int), 1, f) == 0){
        fprintf(stderr, "Failed to get matrix size\n");
        return NULL;
    }

    Matrix* matrix = createMatrix(stolbs, rows);

    if (matrix == NULL)
        return NULL;

    int i = 0; // counter and controler of matrix size

    while (fread(matrix->data[i], sizeof(double) * stolbs, 1, f) == 1 && i < rows){
        //если считали меньше строк чем написано в начале файла, то по i мы это узнаем
        i++;
    }

    if (i != rows){ 
        if (!deleteMatrix(matrix))
            fprintf(stderr, "Matrix was incorrect\n"); // some nums were missed or smth another
        fprintf(stderr, "Wrong matrix size\n");
        return NULL;
    }

    if(fclose(f)){
        if (!deleteMatrix(matrix))
            fprintf(stderr, "Matrix was incorrect\n");
        fprintf(stderr, "Failed to close file\n");
        return NULL;
    }
    return matrix;
}

Matrix* splitByRows(Matrix* matrix, unsigned int startRow, unsigned int length){
    if (matrix == NULL)
        return NULL;

    if (matrix->rowLength - 1 > startRow) 
        return NULL;

    Matrix* result = createMatrix(matrix->stolbLength, length);
    for (int i = 0; i < length; i++){
        memcpy(result->data[i], matrix->data[i + startRow], sizeof(double) * matrix->stolbLength);
        // if (!memcpy(result->data[i], matrix->data[i + startRow], sizeof(double) * matrix->stolbLength))
        //     return NULL;
    }
        

    // here we can delete those rows but i am not sure
    return result;

}
