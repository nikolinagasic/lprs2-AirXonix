#ifndef INPUT_H
#define INPUT_H

#define UP 64
#define DOWN 4
#define LEFT 32
#define RIGHT 8

enum Direction {
    DIRECTION_NONE,
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT
};

typedef enum Direction Direction;

void handle_input(void);
Direction get_direction(void);

#endif
