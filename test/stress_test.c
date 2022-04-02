#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dlfcn.h>
#include "parallel_count.h"
#include "consistent_count.h"

int main(){

    double* resConsist;
    unsigned int rows;
    
    clock_t begin = clock();
    resConsist = countStolbs("/home/temp2/test/test.bin", &rows);
    clock_t end = clock();

    if (!resConsist)
        return 1;
    printf("Static lib wotling time: %f\n", (double)(end-begin));



    void* library = dlopen("libmatrix_dynamic.so", RTLD_LAZY);
    double*(*count)(const char* fileName, unsigned int *row);
    if(!library){
        fprintf(stderr, "Error while loading folowing dynamic lib: %s\n", dlerror());
        return 1;
    } 
    *(double* **)(&count) = dlsym(library, "countStolbs");

    begin = clock();
    double* resParal = (*count)("/home/temp2/test/test.bin", &rows);
    end = clock();

    if(!resParal)
        return 1;
    
    dlclose(library);
    printf("Dynamic lib working time: %f\n", (double)(end-begin));
    


    return 0;
}