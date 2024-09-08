## Main part  

1. Technical Requirements  

- The program is developed in the C language of C11 standard
- The program has a terminal interface
- The program is built with a Makefile that has all the standard targets for GNU-programs: all, install, uninstall, clean, dvi, dist, test, gcov_report
- The game logic library is covered by unit tests using the `check' library. Coverage is at least 80 percent  

2. Architectural Requirements  

- The program is developed in accordance with the principles of structured programming
- The program is decomposed into program modules with division of responsibilities
- Program modules are decomposed into simple and concise functions that do not exceed 1 screen
- The nesting of blocks within functions does not exceed 4
- The project consists of a library that implements the game logic and a terminal interface
- Finite-state machines are used to formalize the logic of the library
- The library and interface must be independent of each other
- The library has one entry point and one exit point
- The library is developed according to the specification given in the materials/library-specification.md file   

3. Functional Requirements  

- The current piece can be rotated using the action button
- The current piece can be moved horizontally using the left/right arrows
- The fall of the current piece can be accelerated by using the down arrow button
- The game can be paused using the "pause" button
- The game can be pre-terminated using the "end game" button
- The game starts after pressing the "start game" button
- Filled rows are destroyed, after which the rows above the destroyed lines are shifted downward
- The game ends when the upper boundary of the playing field is reached
- All 7 pieces mentioned in the README are present in the game
  
- The type of the next piece is determined at the moment of generation of the next piece
- The size of the playing field is ten "pixels" wide and twenty high
- Once a piece reaches the lower boundary of the field or collides with another piece, it must stop, after which the next piece is generated  

4. Implementation Requirements  

- The mechanics of the game must be implemented using FSM
- The FSM of the game must be formalized and represented in the form of a state diagram
- The game must receive countdown and control signals as inputs  

5. Interface Requirements  

- The interface must be implemented in console mode
- The interface must include two parts: the playing field and a panel with additional information
- Additional information fields include: number of points, score record, speed, pause  


## Bonus part  

1. Scoring and game record  

- Scoring mechanics are implemented: 1 row - 100 points, 2 rows - 300 points, 3 rows - 700 points, 4 rows - 1500 points
- The maximum number of points is stored between program runs in a file or embedded DBMS and is available to the player after restarting the game  

2. Level mechanics  

- Level mechanics are implemented. Every time a player gains 600 points, the level increases by 1
- Increasing the level increases the speed at which the pieces move. 
- The maximum number of levels is 10  


