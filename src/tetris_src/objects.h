#ifndef OBJECTS_H
#define OBJECTS_H

typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action
} UserAction_t;

typedef struct {
    int coordinates[8];
    int type;
    int rotate;

    int center_x;
    int center_y;
} TetraMino_bro;

typedef struct {
    int **field;
    int **next;
//    TetraMino_bro tetraMinoBro;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;

} GameInfo_t;

#endif // OBJECTS_H