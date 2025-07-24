cmake_minimum_required(VERSION 3.13)
project(numerical_integral)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS_RELEASE "-O3 -fno-fast-math -fno-unsafe-math-optimizations -frounding-math -march=native")
set(CMAKE_C_FLAGS_DEBUG "-O2 -fno-fast-math -fno-unsafe-math-optimizations -frounding-math -march=native")

add_executable(numerical_integral
        src/program/main.c
        src/ui/gui.c
        src/parser/expression_parser.c
        src/controls/controls.c
        src/integrator/integral.c)

target_include_directories(numerical_integral
        PRIVATE ${GTK3_INCLUDE_DIRS}
        src/ui
        src/parser
        src/integrator
        src/program
        src/memcheck
        src/controls
)

target_link_libraries(numerical_integral PRIVATE ${GTK3_LIBRARIES})

message(STATUS "Current build type: ${CMAKE_BUILD_TYPE}")