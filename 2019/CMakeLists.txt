cmake_minimum_required(VERSION 3.13)

# Put all outputs in a single directory, should you choose to build them all
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin")

add_subdirectory(Template)
add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)