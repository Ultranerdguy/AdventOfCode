cmake_minimum_required(VERSION 3.14)

get_filename_component(AOC_DAY_DIR "CMakeLists.txt/.." ABSOLUTE)
get_filename_component(AOC_DAY "${AOC_DAY_DIR}" NAME)
get_filename_component(AOC_YEAR_DIR "CMakeLists.txt/../.." ABSOLUTE)
get_filename_component(AOC_YEAR "${AOC_YEAR_DIR}" NAME)

project(AoC${AOC_YEAR}_${AOC_DAY})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
add_executable(${PROJECT_NAME} app/main.cpp src/lib.cpp)
add_subdirectory(cmake)