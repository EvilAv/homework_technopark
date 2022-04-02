#include <gtest/gtest.h>
#include <stdlib.h>
#include <stdio.h>

extern "C" {
    #include "matrix.h"
}

TEST(Matrix, CorrectDataCreate){
    Matrix* data = createMatrix(3, 2);
    EXPECT_NE(data, nullptr);
    deleteMatrix(data);
}

TEST(Matrix, ZeroRowsDataCreate){
    Matrix* data = createMatrix(0, 7);
    EXPECT_EQ(data, nullptr);
    deleteMatrix(data);
}

TEST(Matrix, ZeroStolbsDataCreate){
    Matrix* data = createMatrix(8, 0);
    EXPECT_EQ(data, nullptr);
    deleteMatrix(data);
}

TEST(Matrix, CorrectMatrixDelete){
    Matrix* data = createMatrix(3, 2);
    char flag = deleteMatrix(data);
    EXPECT_EQ(flag, TRUE);
}

TEST(Matrix, EmptyMatrixDelete){
    char flag = deleteMatrix(nullptr);
    EXPECT_EQ(flag, FALSE);
}

TEST(Matrix, CorrectFileRead){
    Matrix* data = readFile("/home/temp2/test/test.bin");
    EXPECT_EQ(data->rowLength, 3);
    EXPECT_NE(data, nullptr);
    deleteMatrix(data);
}


int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}