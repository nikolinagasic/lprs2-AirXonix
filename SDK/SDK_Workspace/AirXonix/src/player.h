#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include "map.h"

#define PLAYER_ANIMATION_PHASES 2

extern uint32_t player_sprite[PLAYER_ANIMATION_PHASES][TILE_SIZE * TILE_SIZE];

struct Player {
    int x;
    int y;
    int animation_phase;
};


typedef struct Player Player;

extern Player player;

void init_player(void);
void draw_player(void);
void undraw_player(void);
void animate_player(void);

#endif // PLAYER_H
