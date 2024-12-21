cmake_minimum_required(VERSION 3.13)
project(numerical_integral)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
endif()

add_executable(numerical_integral
        main.c
        gui.c
        expression_parser.c
        integral.c)

target_include_directories(numerical_integral PRIVATE ${GTK3_INCLUDE_DIRS})
target_link_libraries(numerical_integral PRIVATE ${GTK3_LIBRARIES})