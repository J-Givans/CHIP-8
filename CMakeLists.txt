cmake_minimum_required(VERSION 3.20)

project(Chip-8
    VERSION 0.0.1
    DESCRIPTION "An interpreter for the Chip-8 virtual machine"
    LANGUAGES CXX
)

enable_testing()

find_program(CCACHE ccache)

if (CCACHE)
    message("Found ccache")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE}")
endif()

find_package(GTest REQUIRED COMPONENTS gtest_main gmock_main)
find_package(Microsoft.GSL REQUIRED)

add_executable(app src/main.cpp)

add_subdirectory(src)