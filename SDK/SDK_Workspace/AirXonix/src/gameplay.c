#include "enemy.h"
#include "player.h"
#include "map.h"
#include "gameplay.h"


bool check_collisions() {
	int i;

	for (i = 0; i < enemy_count; i++) {
        if (tile_at(enemies[i].x, enemies[i].y) == TILE_DASHED) {
            return true;
        }

        if (enemies[i].x == player.x && enemies[i].y == player.y) {
            return true;
        }
    }

    return false;
}
