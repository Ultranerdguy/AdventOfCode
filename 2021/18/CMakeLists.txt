cmake_minimum_required(VERSION 3.13)

get_filename_component(AOC_DAY_DIR "CMakeLists.txt/.." ABSOLUTE)
get_filename_component(AOC_DAY "${AOC_DAY_DIR}" NAME)
get_filename_component(AOC_YEAR_DIR "CMakeLists.txt/../.." ABSOLUTE)
get_filename_component(AOC_YEAR "${AOC_YEAR_DIR}" NAME)

add_subdirectory(source)