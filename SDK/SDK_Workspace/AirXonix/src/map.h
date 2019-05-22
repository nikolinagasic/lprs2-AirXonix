#ifndef MAP_H
#define MAP_H

#include <stdint.h>

#define TILE_SIZE 16
#define DISPLAY_HEIGHT 240
#define DISPLAY_WIDTH 320
#define MAP_HEIGHT (DISPLAY_HEIGHT / (TILE_SIZE) - 1)
#define MAP_WIDTH (DISPLAY_WIDTH / (TILE_SIZE))

extern uint32_t filled_tile[TILE_SIZE * TILE_SIZE];
extern uint32_t empty_tile[TILE_SIZE * TILE_SIZE];
extern uint32_t dashed_tile[TILE_SIZE * TILE_SIZE];
extern uint32_t clock_image[TILE_SIZE * TILE_SIZE];
extern uint32_t heart_image[TILE_SIZE * TILE_SIZE];

extern uint32_t black_image[TILE_SIZE * TILE_SIZE];

extern uint32_t inner_tile[TILE_SIZE * TILE_SIZE];
extern uint32_t outer_tile[TILE_SIZE * TILE_SIZE];

extern uint8_t map[MAP_HEIGHT * MAP_WIDTH];

extern uint32_t gameOver[TILE_SIZE*TILE_SIZE];

enum TileType {
    TILE_EMPTY,
    TILE_FILLED,
    TILE_DASHED,
    TILE_MAYBE_FILLED,
    TILE_MAYBE_FILLED_INNER,
    TILE_MAYBE_FILLED_OUTER
   // TILE_POTENTIALLY_FILLED
};

typedef enum TileType TileType;

void init_map(void);
void draw_map(void);
void check_fill(void);

TileType tile_at(int x, int y);
void set_tile(int x, int y, TileType type);

#endif
