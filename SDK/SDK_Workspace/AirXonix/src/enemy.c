#include "enemy.h"
#include "drawer.h"
#include "input.h"
#include <stdlib.h>
#include <stdbool.h>

uint32_t enemy_sprite[TILE_SIZE * TILE_SIZE] = {
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0x514FFF, 0x000000, 0x49FF6B, 0x49FF6B, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x514FFF, 0x514FFF, 0x514FFF, 0x000000, 0x49FF6B, 0x49FF6B, 0x49FF6B, 0x49FF6B, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x514FFF, 0x514FFF, 0x514FFF, 0x000000, 0x49FF6B, 0x49FF6B, 0x49FF6B, 0x49FF6B, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0x000000, 0x514FFF, 0x514FFF, 0x514FFF, 0x514FFF, 0x000000, 0x49FF6B, 0x49FF6B, 0x49FF6B, 0x49FF6B, 0x49FF6B, 0x000000, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0x000000, 0xFF954F, 0xFF954F, 0xFF954F, 0xFF954F, 0x000000, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0x000000, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0x000000, 0xFF954F, 0xFF954F, 0xFF954F, 0xFF954F, 0x000000, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0x000000, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF954F, 0xFF954F, 0xFF954F, 0x000000, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF954F, 0xFF954F, 0xFF954F, 0x000000, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0xFFDE3D, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0xFF954F, 0x000000, 0xFFDE3D, 0xFFDE3D, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF
};

Enemy enemies[ENEMY_MAX_COUNT];
int enemy_count;

void init_enemies() {
    enemy_count = 0;
}

void add_enemy(int x, int y) {
    if (enemy_count < ENEMY_MAX_COUNT) {
        enemies[enemy_count].x = x;
        enemies[enemy_count].y = y;
        enemies[enemy_count].direction = (Diagonal)(rand() % DIAGONAL_COUNT);

        draw_sprite(enemy_sprite, x, y);

        ++enemy_count;
    }
}

void draw_enemies() {
	int i;
    for (i = 0; i < enemy_count; i++) {
        draw_sprite(enemy_sprite, enemies[i].x, enemies[i].y);
    }
}

void undraw_enemies() {
	int i;
    for (i = 0; i < enemy_count; i++) {
        undraw_sprite(enemies[i].x, enemies[i].y);
    }
}

bool enemy_exists_at(int x, int y) {
	int i;
    for (i = 0; i < enemy_count; i++) {
        if (enemies[i].x == x && enemies[i].y == y) {
            return true; //vraca tacno ako se lopta nalazi na i-toj koordinati
        }
    }

    return false;
}