cmake_minimum_required(VERSION 3.10)
project(openworks VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Includes
include_directories(include deps)

# Dependencies (Example: looking for libcurl)
find_package(CURL REQUIRED)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Executable
add_executable(openworks ${SOURCES} src/main.cpp)

# Link Libraries
target_link_libraries(openworks PRIVATE CURL::libcurl)

# Testing
enable_testing()
add_subdirectory(tests)
