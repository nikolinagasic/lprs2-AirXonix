#include "input.h"
#include "vga_periph_mem.h"
#include "player.h"
#include "xio.h"
#include "xil_io.h"
#include "xparameters.h"

//provera sta je pritisnuto na dzojstiku
Direction get_direction(void) {
    if ((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & RIGHT) == 0) {
        return DIRECTION_RIGHT;
    }
    else if ((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & LEFT) == 0) {
        return DIRECTION_LEFT;
    }
    else if ((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & UP) == 0) {
        return DIRECTION_UP;
    }
    else if ((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & DOWN) == 0) {
        return DIRECTION_DOWN;
    }

    return DIRECTION_NONE;
}

static Direction opposite_direction(Direction direction) {
    switch (direction) {
    case DIRECTION_UP:
        return DIRECTION_DOWN;
    case DIRECTION_DOWN:
        return DIRECTION_UP;
    case DIRECTION_LEFT:
        return DIRECTION_RIGHT;
    case DIRECTION_RIGHT:
        return DIRECTION_LEFT;
    default:
        return DIRECTION_NONE;
    }
}

void handle_input(void) {
    static Direction active_direction = DIRECTION_NONE; //smer kretanja igraca

    const Direction current_direction = get_direction();
    const TileType player_tile = tile_at(player.x, player.y);

    if (player_tile == TILE_FILLED) {
        active_direction = current_direction;
    }
    else if (active_direction == DIRECTION_NONE) {
        active_direction = current_direction;
    }
    else if (current_direction != DIRECTION_NONE && current_direction != opposite_direction(active_direction)) {
        active_direction = current_direction;
    }

    switch (active_direction) {
    case DIRECTION_UP:
        if (player.y > 0) {
            --(player.y);
        }
        break;

    case DIRECTION_DOWN:
        if (player.y < MAP_HEIGHT - 1) {
            ++(player.y);
        }
        break;

    case DIRECTION_LEFT:
        if (player.x > 0) {
            --(player.x);
        }
        break;

    case DIRECTION_RIGHT:
        if (player.x < MAP_WIDTH - 1) {
            ++(player.x);
        }
        break;

    default:
        break;
    }
}
