cmake_minimum_required(VERSION 3.10)
project(des)

# Include directories
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")

# Find all source files in the src directory
file(GLOB_RECURSE PROJECT_FILES
        "${INCLUDE_DIR}/*.h"
        "${SOURCE_DIR}/*.c"
)

# Add executable for this project
add_executable(des ${PROJECT_FILES}
        src/des.c
        include/des.h)

target_include_directories(des PRIVATE ${INCLUDE_DIR})
target_link_libraries(des m)