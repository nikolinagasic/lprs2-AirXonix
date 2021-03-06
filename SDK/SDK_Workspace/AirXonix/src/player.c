#include "player.h"
#include "vga_periph_mem.h"
#include "drawer.h"

uint32_t player_sprite[PLAYER_ANIMATION_PHASES][TILE_SIZE * TILE_SIZE] = {
    {
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF,
        0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF,
        0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0xFFFEFC, 0x3F59FF, 0xFFFEFC, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF,
        0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF,
        0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0xFFFEFC, 0x3F59FF, 0xFFFEFC, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF,
        0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF,
        0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF,
        0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF
    },
    {
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF,
        0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF,
        0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xF7FCFF, 0x3F59FF, 0xF7FCFF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF,
        0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF,
        0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xF7FCFF, 0x3F59FF, 0xF7FCFF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF,
        0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF,
        0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF,
        0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x3F59FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x3F59FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
        0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0x7FB6FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF
    }
};


Player player;

void init_player(void) {
    player.x = MAP_WIDTH / 2 - 1;
    player.y = MAP_HEIGHT - 1;
    player.animation_phase = 0;
}

void draw_player(void) {
    draw_sprite(player_sprite[player.animation_phase], player.x, player.y);
}

void undraw_player(void) {
    undraw_sprite(player.x, player.y);
}

void animate_player(void) {
    player.animation_phase = (player.animation_phase + 1) % PLAYER_ANIMATION_PHASES;
}
