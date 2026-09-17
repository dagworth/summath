cmake_minimum_required(VERSION 3.16)
project(summath LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(summath
    src/main.cpp
    src/solve.cpp
    src/calc/lexer.cpp
)
target_link_libraries(summath PRIVATE Qt6::Widgets)