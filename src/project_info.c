#include "project_info.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Date* dateCreate(unsigned short day, unsigned short month, unsigned short year){
    Date* date = (Date*)malloc(sizeof(Date));
    if (date == NULL) return NULL;
    if (!day || !month || month > MONTH_COUNT || day > DAY_COUNT || year > MAX_YEAR || year < MIN_YEAR) return NULL;

    date->day = day;
    date->month = month;
    date->year = year;

    return date;
}
Project* projectCreate(Date* start, Date* end, char* name, char* system, unsigned char priority, char* boss){
    Project* project = (Project*)malloc(sizeof(Project));
    if(project == NULL) return NULL;
    if (start == NULL || end == NULL) return NULL;

    project->startDate = start;
    project->endDate = end;
    project->projectName = name;
    project->systemName = system;
    project->priority = priority;
    project->bossName = boss;

    return project;
}
ProjectArray* getDefaultDataBase(){
    ProjectArray* arr = (ProjectArray*)malloc(sizeof(ProjectArray));
    if (arr == NULL) return NULL;

    arr->length = PROJECT_COUNT;
    arr->projects = (Project**)malloc(PROJECT_COUNT * sizeof(Project));

    char *bossNames[PROJECT_COUNT] = {"Azazel", "Nicolas Cage", "Vanya", "L"};
    char *systemsNames[PROJECT_COUNT] = {"Linux", "Windows", "MacOS", "DOS"};
    char *projectNames[PROJECT_COUNT] = {"NFT", "Fight-club", "Cucumber", "FakeProject"};



    for(int i=0; i< PROJECT_COUNT; i++){
        unsigned char tempNum = (2*i) % 12 +1;
        arr->projects[i] = projectCreate(dateCreate(tempNum+10, tempNum, 2021), dateCreate(tempNum+3, tempNum, 2022), projectNames[i], systemsNames[i], i%2, bossNames[i]);
    }

    return arr;
}
void printProject(Project* project){
    if (project == NULL) printf("Something wrong with data");
    else{
            printf("-----------------------------------------\n");
            printf("Project \"%s\" for %s controlled by %s \n", project->projectName, project->systemName, project->bossName);
            printf("Started %d/%d/%d \n", project->startDate->day, project->startDate->month, project->startDate->year);
            printf("Will be ended %d/%d/%d \n", project->endDate->day, project->endDate->month, project->endDate->year);
            printf("Project's priority: %d \n", project->priority);
    }
}
void copy(Project* a, Project* b){ // copy from b to a
    a->startDate = b->startDate;
    a->endDate = b->endDate;
    a->projectName = b->projectName;
    a->systemName = b->systemName;
    a->priority = b->priority;
    a->bossName = b->bossName;
}
void swap(Project* a, Project* b){
    Project* temp = (Project*)malloc(sizeof(Project));
    copy(temp, a);
    copy(a, b);
    copy(b, temp);
    free(temp);
}
void sortProjects(ProjectArray* arr){ // the way to group projects by priority
        for (int i=0; i<arr->length; i++){
            Project* upperElement = arr->projects[i];
            for (int j=i; j > 0 && arr->projects[j-1]->priority > arr->projects[j]->priority; j--)
                swap(arr->projects[j-1], arr->projects[j]);
    }
}
void deleteArray(ProjectArray* arr){
    for (int i =0; i < arr->length; i++){
        free(arr->projects[i]->startDate);
        free(arr->projects[i]->endDate);
        free(arr->projects[i]);
    }
    free(arr);
}
short findProjectsInQuarter(unsigned short month, unsigned short year, ProjectArray* arr, char flag){
    if (arr == NULL){
        if (flag) printf("Something wrong with input database\n");
        return -2;
    }
    unsigned char quarter = (month-1) / 3;

    if (quarter > 3) {
        if (flag) printf("Entered date were wrong\n");
        return -1;
    }
    sortProjects(arr);
    unsigned char counter = 0;
    for (int i=0; i< arr->length; i++){
        Project* shortcut = arr->projects[i];
        if ((shortcut->endDate->month-1) / 3 == quarter && shortcut->endDate->year == year){
            counter++;
            if (flag) printProject(shortcut);
        }
    }
    if (!counter) if (flag) printf("There are no any projects in this quarter\n");
    return counter;
}

