cmake_minimum_required(VERSION 3.13)
project(AoC${AOC_YEAR}_${AOC_DAY})

include_directories(include)
add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(cmake)