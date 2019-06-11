#include "vga_periph_mem.h"
#include "drawer.h"
#include "map.h"
#include "vga_periph_mem.h"

void draw_sprite(const uint32_t *sprite, int x, int y) {
    int i;
    int j;

    for (i = 0; i < TILE_SIZE; i++) {
        for (j = 0; j < TILE_SIZE; j++) {
            const int row = TILE_SIZE * x + i;
            const int col = TILE_SIZE * y + j;
            const uint32_t color = sprite[j * TILE_SIZE + i];

            if (color != INVISIBLE_COLOR) {
                SET_PIXEL(row, col, sprite[j * TILE_SIZE + i]);
            }    //z
            else if (tile_at(x, y) == TILE_FILLED) {
                SET_PIXEL(row, col, filled_tile[j * TILE_SIZE + i]);
            }
            else {
                SET_PIXEL(row, col, empty_tile[j * TILE_SIZE + i]);
            }
        }
    }
}

void undraw_sprite(int x, int y) {
    int i;
    int j;

    for (i = 0; i < TILE_SIZE; i++) {
        for (j = 0; j < TILE_SIZE; j++) {
            const int row = TILE_SIZE * x + i;
            const int col = TILE_SIZE * y + j;

            if (tile_at(x, y) == TILE_FILLED) {
                SET_PIXEL(row, col, filled_tile[j * TILE_SIZE + i]);
            }
            else {
                SET_PIXEL(row, col, empty_tile[j * TILE_SIZE + i]);
            }
        }
    }
}



void delete_heart(int x, int y) {
    int i;
    int j;

    for (i = 0; i < TILE_SIZE; i++) {
        for (j = 0; j < TILE_SIZE; j++) {
            const int row = TILE_SIZE * x + i;
            const int col = TILE_SIZE * y + j;
             SET_PIXEL(row, col, 0x000000);

        }
    }
}
