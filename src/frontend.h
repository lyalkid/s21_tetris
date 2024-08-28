#ifndef FRONTEND_H
#define FRONTEND_H

#include <stdio.h>

#define ROWS 20
#define COLS 10


typedef struct 
{
    int rotate;
    int type;
} Figure_type;




void render();
#endif // FRONTEND_H