#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <sys/shm.h>
#include <wait.h>
#include <unistd.h>
#include "parallel_count.h"

// to split matrix into the right amount of rows
unsigned int rowsInCurProc(procInfo p){
    if (p.id == p.totalAmount - 1)
        return (p.rowsInLastProc);
    else
        return p.rowsInProc;

}

double* countStolbs(const char* fileName, unsigned int *r) {
    Matrix* matrix = readFile(fileName);
    *r = matrix->rowLength;
    if (matrix == NULL)
        return NULL;
    

    // get amount of available processes
    int procAmount = get_nprocs();
    int pidArray[procAmount];

    unsigned int rowsInProc = matrix->rowLength / procAmount;
    unsigned int rowsInLastProc = matrix->rowLength % procAmount;
    // if we got too much available processes
    if (rowsInProc == 0)
        rowsInProc = 1;

    // Создаем shared memory, куда будут записаны самые молодые и возрастные сотрудники
    int shmId = shmget(IPC_PRIVATE, sizeof(double) * matrix->stolbLength * 2, 0644);
    if (shmId == -1) {
        fprintf(stderr, "Failed to create shared memory\n");
        return NULL;
    }

    for (int i = 0; i < procAmount; i++) {
        int pid = fork();
        if (pid < 0) {
            fprintf(stderr, "Failed to fork child\n");
            return NULL;
        } 
        else if (pid > 0) { // put children in array
            pidArray[i] = pid;
        } 
        else if (pid == 0) { // switch to current process
            procInfo info = {
                    rowsInProc,
                    i,
                    procAmount,
                    rowsInLastProc
            };
            // configure current sub matrix
            unsigned int size = rowsInCurProc(info);
            
            Matrix* temp = splitByRows(matrix, i * rowsInProc, size);
            if (temp == NULL)
                exit(1);

            double* subResult = (double*)malloc(sizeof(double) * temp->stolbLength);
            if (subResult == NULL)
                    exit(1);
            memset(subResult, 0.0, sizeof(double) * temp->stolbLength); // fill with 0

            for (int j = 0; j < temp->rowLength; j++){
                for (int k = 0; k < temp->stolbLength; k++)
                    subResult[k] += temp->data[j][k];
            }

            // attach buffer to shared memory to write result
            double* sharedMemorySubRes = (double*)shmat(shmId, NULL, 0);
            if (sharedMemorySubRes == (void*)  -1) {
                fprintf(stderr, "Failed to attach shared memory\n");
                exit(2);
            }

            int startIndex = rowsInProc * i * 2; // because we write smth before
            for (int j = 0; j < size; j++) {
                sharedMemorySubRes[startIndex + j] = subResult[j];
            }
            if (shmdt(sharedMemorySubRes) == -1) { // detach the buffer
                fprintf(stderr, "Failed to dettach shared memory\n");
                return NULL;
            }

            if (deleteMatrix(temp)) 
                exit(3);
            free(subResult);

            exit(0);
        }
    }

    // wait until all processes finish
    for (int i = 0; i < procAmount; i++) {
        int procStatus;
        waitpid(pidArray[i], &procStatus, 0);
    }
    
    // Считываем данные из shared memory
    double *result = (double*)shmat(shmId, 0, SHM_RDONLY);
    if (result == (void*) -1) {
        fprintf(stderr, "Failed to attach shared memory\n");
        return NULL;
    }
    double *res = (double*)malloc(sizeof(double) * matrix->stolbLength);
    memcpy(res, result, sizeof(double) * matrix->stolbLength);
    
    if (shmdt(result) == -1) {
        fprintf(stderr, "Failed to detach shared memory\n");
        return NULL;
    }
    if (shmctl(shmId, IPC_RMID, 0) == -1) {
        fprintf(stderr, "Failed to destroy shared memory\n");
        return NULL;
    }
    return result;
}