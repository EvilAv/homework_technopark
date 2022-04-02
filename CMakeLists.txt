cmake_minimum_required(VERSION 3.14)
project(matrix)

include_directories(include)
include_directories(src)
include_directories(test)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-pedantic -fprofile-arcs -ftest-coverage -O0")


set(LIB_STATIC_SOURCE_FILES     
    src/consistent_count.c
    include/matrix.h
    src/matrix.c
    include/consistent_count.h)

set(LIB_DYNAMIC_SOURCE_FILES 
    src/parallel_count.c
    include/matrix.h
    src/matrix.c
    include/parallel_count.h)

add_library(matrix_static STATIC ${LIB_STATIC_SOURCE_FILES})

add_library(matrix_dynamic SHARED ${LIB_DYNAMIC_SOURCE_FILES})

add_executable(stress_test test/stress_test.c)
target_include_directories(stress_test PUBLIC test)
target_link_libraries(stress_test matrix_static)
target_link_libraries(stress_test matrix_dynamic ${CMAKE_DL_LIBS})

enable_testing()

find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})
message(${GTEST_LIBRARIES})
add_executable(test_static
    test/tests.cpp)
target_link_libraries(test_static matrix_static)
target_link_libraries(test_static gtest ${CMAKE_THREAD_LIBS_INIT})

add_executable(test_dynamic
    test/tests.cpp)
target_link_libraries(test_dynamic matrix_dynamic)
target_link_libraries(test_dynamic gtest ${CMAKE_THREAD_LIBS_INIT})

