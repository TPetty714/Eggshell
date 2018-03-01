cmake_minimum_required(VERSION 3.6)
project(project2_interactive_shell)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)

add_executable(project2_interactive_shell ${SOURCE_FILES})