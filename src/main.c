#include "project_info.h"
#include <stdlib.h>
#include <stdio.h>

int main(){

    unsigned short month = 0; unsigned short year =0;
    printf("Enter date of chosen quarter in format MM YYYY\n");
    scanf("%hu %hu", &month, &year);

    while (month > MONTH_COUNT || year > MAX_YEAR || month == 0 || year < MIN_YEAR){
        printf("You entered wrong data, try one more time\n");
            printf("Enter date of chosen quarter in format MM YYYY\n");
    scanf("%hu %hu", &month, &year);
    }
    
    ProjectArray* temp = getDefaultDataBase();
    findProjectsInQuarter(month, year, temp, 1);
    deleteArray(temp);
}