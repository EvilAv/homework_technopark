#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    FILE *fp;
    unsigned int square = 3;
    double* temp = (double*)malloc(sizeof(double) * (square * square));
    for (int i = 0; i < square * square; i++)
        temp[i] = 0.02 * i;
    if ((fp=fopen("test.bin", "wb"))==NULL) {
        printf("Cannot open file.\n");
        exit (1);
    }
    fwrite(&square, sizeof(unsigned int), 2, fp);
    fwrite(&temp, sizeof(float), 1, fp);
    fclose (fp);
    free(temp);
    return 0;
}