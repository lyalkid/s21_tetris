cmake_minimum_required(VERSION 3.26)
project(tetris C)

set(CMAKE_C_STANDARD 11)

add_definitions(-Ddebug_bro)
add_executable(tetris
        src/brick_game/tetris/tetris_bro.c
        src/gui/cli/frontend.c
        src/brick_game/tetris/src/backend.c
#        src/brick_game/tetris/src/fsm.c
        src/brick_game/tetris/tetris_bro.c
#        src/brick_game/tetris/src/fsm.c
        src/brick_game/tetris/src/fsm_main.c

)
target_link_libraries(tetris m ncurses)