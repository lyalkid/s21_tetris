cmake_minimum_required(VERSION 3.26)
project(tetris C)

set(CMAKE_C_STANDARD 11)

add_executable(tetris
        src/tetris_bro.c
        src/tetris_src/frontend.c
        src/tetris_src/backend.c

)
target_link_libraries(tetris m ncurses)