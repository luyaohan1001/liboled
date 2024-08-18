# CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(liboled VERSION 1.0.0 LANGUAGES C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Ensure debug flags are enabled.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

add_library(liboled 
    src/framebuffer.c
    src/graphics.c
)

# Specify include directories for the library
target_include_directories(liboled PUBLIC 
    ${PROJECT_SOURCE_DIR}/src
)

# Create the executable
add_executable(test test.c)

# Link the library to the executable
target_link_libraries(test PRIVATE liboled)