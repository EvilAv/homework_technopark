#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "project_info.h"
}

TEST(Project, CorrectDateCreate){
    Date* date = dateCreate(12, 3, 2018);
    EXPECT_NE(date, nullptr);
    EXPECT_EQ(date->day, 12);
    free(date);
}

TEST(Project, ZeroDateCreate){
    Date* date = dateCreate(0, 2, 0);
    EXPECT_EQ(date, nullptr);
    free(date);
}

TEST(Project, IncorrectDateCreate){
    Date* date = dateCreate(2, 22, 1986);
    EXPECT_EQ(date, nullptr);
    free(date);
}

TEST(Project, CorrectProjectCreate){
    Date* date = dateCreate(10, 2, 2000);
    char* testName = (char*)"Test1";
    Project* project = projectCreate(date, date, testName, testName, 12, testName);
    EXPECT_NE(project, nullptr);
    EXPECT_EQ(project->bossName, "Test1");
    free(date);
    free(project);
}

TEST(Project, IncorrectProjectCreate){
    Date* date = dateCreate(0, 2, 2000);
    char* testName = (char*)"Test2";
    Project* project = projectCreate(date, date, testName, testName, 12, testName);
    EXPECT_EQ(project, nullptr);
    free(date);
    free(project);
}

TEST(Project, ProjectsInFirstQuarter){
    ProjectArray* temp = getDefaultDataBase();
    int res = findProjectsInQuarter(1, 2022, temp, 0);
    EXPECT_NE(res, -1);
    EXPECT_NE(res, -2);
    EXPECT_EQ(res, 2);
    deleteArray(temp);
}

TEST(Project, ProjectsInSecondQuarter){
    ProjectArray* temp = getDefaultDataBase();
    int res = findProjectsInQuarter(4, 2022, temp, 0);
    EXPECT_NE(res, -1);
    EXPECT_NE(res, -2);
    EXPECT_EQ(res, 1);
    deleteArray(temp);
}

TEST(Project, ProjectsInThirdQuarter){
    ProjectArray* temp = getDefaultDataBase();
    int res = findProjectsInQuarter(7, 2022, temp, 0);
    EXPECT_NE(res, -1);
    EXPECT_NE(res, -2);
    EXPECT_EQ(res, 1);
    deleteArray(temp);
}

TEST(Project, ProjectsInFourthQuarter){
    ProjectArray* temp = getDefaultDataBase();
    int res = findProjectsInQuarter(10, 2022, temp, 0);
    EXPECT_NE(res, -1);
    EXPECT_NE(res, -2);
    EXPECT_EQ(res, 0);
    deleteArray(temp);
}

TEST(Project, ProjectsInWrongMonth){
    ProjectArray* temp = getDefaultDataBase();
    int res = findProjectsInQuarter(52, 2022, temp, 0);
    EXPECT_NE(res, 0);
    EXPECT_NE(res, -2);
    EXPECT_EQ(res, -1);
    deleteArray(temp);
}

TEST(Project, ProjectsInNoArray){
    ProjectArray* temp = {};
    int res = findProjectsInQuarter(10, 2022, temp, 0);
    //EXPECT_NE(res, -1);
    //EXPECT_NE(res, 0);
    EXPECT_EQ(res, -2);
}
int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}