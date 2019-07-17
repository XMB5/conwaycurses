cmake_minimum_required(VERSION 3.14)
project(conway C)

set(CMAKE_C_STANDARD 99)

add_executable(conway main.c logic.c logic.h)

target_link_libraries(conway curses)