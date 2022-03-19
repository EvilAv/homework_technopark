cmake_minimum_required(VERSION 3.14)
project(project_info)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-pedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "-pedantic -fprofile-arcs -ftest-coverage -O0")

set(LIB_SOURCE_FILES src/project_info.c)
add_Library(study_iz1_lib STATIC ${LIB_SOURCE_FILES})
include_directories(include)
include_directories(src)

add_executable(main.out
    include/project_info.h  
    src/main.c)
target_link_libraries(main.out PRIVATE study_iz1_lib)


enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIR})
message(${GTEST_LIBRARIES})
add_executable(tests src/tests.cpp)

target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)
target_link_libraries(tests study_iz1_lib)