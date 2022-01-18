cmake_minimum_required(VERSION 3.10)

project(c-structs VERSION 0.1)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(src)

add_subdirectory(sandbox)

enable_testing()
add_subdirectory(tests)
