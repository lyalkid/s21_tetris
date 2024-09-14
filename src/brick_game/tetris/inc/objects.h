#ifndef OBJECTS_H_
#define OBJECTS_H_

enum status { ERROR, OK };

enum figures { T, J, L, I, S, Z, O };
enum degrees { COMPLETE, RIGHT, STRAIGHT, REFLEX };

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

    int score;
    int high_score;
    int level;
    int speed;
    int pause;
    int **field;
    int **next;
} GameInfo_t;

typedef struct {
    int type;
    int rotate;
    int center_x;
    int center_y;
    int coordinates[8];
} TetraMino_bro;

typedef struct {
    TetraMino_bro tetraMinoBro;
    UserAction_t userAction;
    GameInfo_t gameInfo;
}
Game_Objects_t;

#endif // OBJECTS_H_