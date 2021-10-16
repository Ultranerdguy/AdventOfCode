cmake_minimum_required(VERSION 3.14)

set(AoC_Current_Library "${PROJECT_NAME}_Library")
add_library(${AoC_Current_Library} lib.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${AoC_Current_Library})