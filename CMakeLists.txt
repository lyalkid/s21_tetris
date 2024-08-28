cmake_minimum_required(VERSION 3.26)
project(tetris C)

set(CMAKE_C_STANDARD 11)

add_executable(tetris
        src/tetris_bro.c
        code-samples/frogger/inc/frogger.h
        code-samples/frogger/src/frogger.c
)
target_link_libraries(tetris m ncurses)