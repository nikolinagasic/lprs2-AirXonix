#ifndef ENEMY_H
#define ENEMY_H

#include <stdbool.h>
#include "map.h"
#include "input.h"

enum Diagonal {
    DIAGONAL_TOP_RIGHT,
    DIAGONAL_TOP_LEFT,
    DIAGONAL_BOTTOM_RIGHT,
    DIAGONAL_BOTTOM_LEFT,
    DIAGONAL_COUNT
};

typedef enum Diagonal Diagonal;
//coskovi
static inline Diagonal opposite_diagonal(Diagonal diagonal) {
    switch (diagonal) {
    case DIAGONAL_TOP_RIGHT: //gornji desni cosak spusta se dole levo
        return DIAGONAL_BOTTOM_LEFT;
    case DIAGONAL_TOP_LEFT:
        return DIAGONAL_BOTTOM_RIGHT;
    case DIAGONAL_BOTTOM_RIGHT:
        return DIAGONAL_TOP_LEFT;
    default:
        return DIAGONAL_TOP_RIGHT;
    }
}
//strane
static inline Diagonal complementary_diagonal(Diagonal diagonal, Direction side) {
    switch (diagonal) {
    case DIAGONAL_TOP_RIGHT:
        if (side == DIRECTION_UP) {
            return DIAGONAL_BOTTOM_RIGHT;
        }
        else {
            return DIAGONAL_TOP_LEFT;
        }

    case DIAGONAL_TOP_LEFT:
        if (side == DIRECTION_UP) {
            return DIAGONAL_BOTTOM_LEFT;
        }
        else {
            return DIAGONAL_TOP_RIGHT;
        }

    case DIAGONAL_BOTTOM_RIGHT:
        if (side == DIRECTION_DOWN) {
            return DIAGONAL_TOP_RIGHT;
        }
        else {
            return DIAGONAL_BOTTOM_LEFT;
        }

    default:
        if (side == DIRECTION_DOWN) {
            return DIAGONAL_TOP_LEFT;
        }
        else {
            return DIAGONAL_BOTTOM_RIGHT;
        }
    }
}

extern uint32_t enemy_sprite[TILE_SIZE * TILE_SIZE];

struct Enemy {
    int x;
    int y;
    Diagonal direction;
};

typedef struct Enemy Enemy;

#define ENEMY_MAX_COUNT 5
extern Enemy enemies[ENEMY_MAX_COUNT];
extern int enemy_count;

void init_enemies();
void add_enemy(int x, int y);
void draw_enemies();
void undraw_enemies();
bool enemy_exists_at(int x, int y);

#endif
