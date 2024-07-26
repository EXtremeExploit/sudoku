cmake_minimum_required(VERSION 3.5.0)
project(sudoku VERSION 0.1.0 LANGUAGES C CXX)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(sudoku sudoku.cpp generator.cpp)

target_link_libraries(sudoku ${CURSES_LIBRARIES})