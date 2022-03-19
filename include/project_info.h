#ifndef PROJECT_INFO_H
#define PROJECT_INFO_H

#define PROJECT_COUNT 4
#define MONTH_COUNT 12
#define DAY_COUNT 31
#define MAX_YEAR 2140
#define MIN_YEAR 1940

typedef struct Date{
    unsigned short day;
    unsigned short month;
    unsigned short year;
}Date;

typedef struct Project{
    // start date
    Date* startDate;
    // end date
    Date* endDate;
    char* projectName;
    char* systemName;
    // 0 - highest priority 255 - lowest
    unsigned short priority;
    char* bossName;
}Project;

typedef struct ProjectArray{
    unsigned int length;
    Project** projects;
    
}ProjectArray;

Date* dateCreate(unsigned short day, unsigned short month, unsigned short year);
Project* projectCreate(Date* start, Date* end, char* name, char* system, unsigned char priority, char* boss);
ProjectArray* getDefaultDataBase();
void printProject(Project* project);
void copy(Project* a, Project* b);
void swap(Project* a, Project* b);
void sortProjects(ProjectArray* arr);
short findProjectsInQuarter(unsigned short month, unsigned short year, ProjectArray* arr, char flag);
void deleteArray(ProjectArray* arr);

#endif