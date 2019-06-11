#include <stdlib.h>
#include "platform.h"
#include "vga_periph_mem.h"
#include "player.h"
#include "input.h"
#include "drawer.h"
#include "map.h"
#include "enemy.h"
#include "xparameters.h"
#include "vga_periph_mem.h"
#include "xintc.h"
#include "gameplay.h"

#define DIRT 'D'
#define CREEP 0
#define CREEP4 4
#define WIN_PERCENTAGE 30




void handle_top_right(int enemy_index) {
    const int x = enemies[enemy_index].x;
    const int y = enemies[enemy_index].y;

    if (tile_at(x, y - 1) == TILE_FILLED || enemy_exists_at(x, y - 1)) {
        enemies[enemy_index].direction = complementary_diagonal(enemies[enemy_index].direction, DIRECTION_UP);//odbija se od direction up
    }
    else if (tile_at(x + 1, y) == TILE_FILLED || enemy_exists_at(x + 1, y)) {
        enemies[enemy_index].direction = complementary_diagonal(enemies[enemy_index].direction, DIRECTION_RIGHT);
    }
    else if (tile_at(x + 1, y - 1) == TILE_FILLED || enemy_exists_at(x + 1, y - 1)) {//cosak
        enemies[enemy_index].direction = opposite_diagonal(enemies[enemy_index].direction);
    }
    else {
        ++(enemies[enemy_index].x);
        --(enemies[enemy_index].y);
    }
}

void handle_top_left(int enemy_index) {
    const int x = enemies[enemy_index].x;
    const int y = enemies[enemy_index].y;

    if (tile_at(x, y - 1) == TILE_FILLED || enemy_exists_at(x, y - 1)) {
        enemies[enemy_index].direction = complementary_diagonal(enemies[enemy_index].direction, DIRECTION_UP);
    }
    else if (tile_at(x - 1, y) == TILE_FILLED || enemy_exists_at(x - 1, y)) {
        enemies[enemy_index].direction = complementary_diagonal(enemies[enemy_index].direction, DIRECTION_LEFT);
    }
    else if (tile_at(x - 1, y - 1) == TILE_FILLED || enemy_exists_at(x - 1, y - 1)) {
        enemies[enemy_index].direction = opposite_diagonal(enemies[enemy_index].direction);
    }
    else {
        --(enemies[enemy_index].x);
        --(enemies[enemy_index].y);
    }
}

void handle_bottom_right(int enemy_index) {
    const int x = enemies[enemy_index].x;
    const int y = enemies[enemy_index].y;

    if (tile_at(x, y + 1) == TILE_FILLED || enemy_exists_at(x, y + 1)) {
        enemies[enemy_index].direction = complementary_diagonal(enemies[enemy_index].direction, DIRECTION_DOWN);
    }
    else if (tile_at(x + 1, y) == TILE_FILLED || enemy_exists_at(x + 1, y)) {
        enemies[enemy_index].direction = complementary_diagonal(enemies[enemy_index].direction, DIRECTION_RIGHT);
    }
    else if (tile_at(x + 1, y + 1) == TILE_FILLED || enemy_exists_at(x + 1, y + 1)) {
        enemies[enemy_index].direction = opposite_diagonal(enemies[enemy_index].direction);
    }
    else {
        ++(enemies[enemy_index].x);
        ++(enemies[enemy_index].y);
    }
}

void handle_bottom_left(int enemy_index) {
    const int x = enemies[enemy_index].x;
    const int y = enemies[enemy_index].y;

    if (tile_at(x, y + 1) == TILE_FILLED || enemy_exists_at(x, y + 1)) {
        enemies[enemy_index].direction = complementary_diagonal(enemies[enemy_index].direction, DIRECTION_DOWN);
    }
    else if (tile_at(x - 1, y) == TILE_FILLED || enemy_exists_at(x - 1, y)) {
        enemies[enemy_index].direction = complementary_diagonal(enemies[enemy_index].direction, DIRECTION_LEFT);
    }
    else if (tile_at(x - 1, y + 1) == TILE_FILLED || enemy_exists_at(x - 1, y + 1)) {
        enemies[enemy_index].direction = opposite_diagonal(enemies[enemy_index].direction);
    }
    else {
        --(enemies[enemy_index].x);
        ++(enemies[enemy_index].y);
    }
}

#define INPUT_TIMING 10
#define ENEMY_SPEED 20
#define ANIMATION_SPEED 5

static bool game_running = false;
static unsigned ticks = 0;
static unsigned seconds = 0;
static unsigned minutes = 0;
static unsigned lives = 3;
static bool skip_handle_death = false;

#define INFO_LINE MAP_HEIGHT
//pozove se kad igrac umre
static void handle_death() {
	unsigned i, j;

	if (skip_handle_death) {
		return;
	}

	if (lives > 1) {
		--lives;

		//sklanjaju se sva popunjena i isprekidana polja
	    for (j = 1; j < MAP_HEIGHT - 1; j++) {
	        for (i = 1; i < MAP_WIDTH - 1; i++) {
	            TileType type = tile_at(i, j);
	            //sklanja dashed i potencijalno popunjene
	            if (type == TILE_MAYBE_FILLED || type == TILE_DASHED) {
	                set_tile(i, j, TILE_EMPTY);
	                draw_sprite(empty_tile, i, j);
	            }

	        }
	    }

	    //OBRISE SRCE I POZADINA OSTANE CRNA NE BUDE ROZE KAO PRE
	    delete_heart(0,INFO_LINE);
	    delete_heart(1,INFO_LINE);
	   	delete_heart(2,INFO_LINE);
		//delete_heart(19,INFO_LINE);

	   	//crta onoliko srca koliko je ostalo
		for (i = 0 ; i < lives ; i++) {
		    draw_sprite(heart_image, i, INFO_LINE);

		}

		//vracanje igraca na pocetni polozaj
		player.x = MAP_WIDTH / 2 - 1;
		player.y = MAP_HEIGHT - 1;
	}
	else {

		int i,j;
			while(1){
				for (i = 0; i < MAP_WIDTH; i++) {
					for (j = 0; j < MAP_HEIGHT; j++) {
						//draw_sprite(clock_image,i,j);
						draw_sprite(sad,i,j);

					}
					draw_sprite(black_image,i,INFO_LINE);
					}

		}



		game_running = false;

	}
}

//logika igre
void vga_interrupt(void *arg) {
	(void)arg;

	skip_handle_death = false;

    if (!game_running) {
        return;
    }


    undraw_enemies();

    if (ticks % INPUT_TIMING == 0) {
        const TileType player_tile = tile_at(player.x, player.y);

		if (player_tile != TILE_FILLED) {
			draw_sprite(dashed_tile, player.x, player.y);
			set_tile(player.x, player.y, TILE_DASHED);
		}
		else {
			undraw_player();
			check_fill();
		}

		handle_input();

		if (player_tile == TILE_DASHED) {
			handle_death();
			skip_handle_death = true;
		}
    }


    if (check_collisions()) {
		handle_death();
		skip_handle_death = true;
    }

    if (ticks % ENEMY_SPEED == 0) {
    	int i;
        for (i = 0; i < enemy_count; i++) {
            switch (enemies[i].direction) {
            case DIAGONAL_TOP_RIGHT:
                handle_top_right(i);
                break;

            case DIAGONAL_TOP_LEFT:
                handle_top_left(i);
                break;

            case DIAGONAL_BOTTOM_LEFT:
                handle_bottom_left(i);
                break;

            default:
                handle_bottom_right(i);
                break;
            }
        }
    }

    if (check_collisions()) {
		handle_death();
		skip_handle_death = true;
    }
    /////////////////////////////////////////////////////////////////////////

   print_percentage();


   if (get_percentage() > WIN_PERCENTAGE) {unsigned i, j;

	   	if (skip_handle_death) {
	   		return;
	   	}

	   	if (lives > 1) {
	   		--lives;

	   	    for (j = 1; j < MAP_HEIGHT - 1; j++) {
	   	        for (i = 1; i < MAP_WIDTH - 1; i++) {
	   	            TileType type = tile_at(i, j);

	   	            if (type == TILE_MAYBE_FILLED || type == TILE_DASHED) {
	   	                set_tile(i, j, TILE_EMPTY);
	   	                draw_sprite(heart_image, i, INFO_LINE);
	   	            }

	   	        }
	   	    }

	   	    delete_heart(0,INFO_LINE);
	   	    delete_heart(1,INFO_LINE);
	   	   	delete_heart(2,INFO_LINE);

	   		for (i = 0 ; i < lives ; i++) {
	   		    draw_sprite(heart_image, i, INFO_LINE);

	   		}

	   		player.x = MAP_WIDTH / 2 - 1;
	   		player.y = MAP_HEIGHT - 1;
	   	}
	   	else {

	   		int i,j;
	   			while(1){
	   				for (i = 0; i < MAP_WIDTH; i++) {
	   					for (j = 0; j < MAP_HEIGHT; j++) {
	   						draw_sprite(happy, i, j);
	   					}
	   					draw_sprite(black_image,i,INFO_LINE);
	   					}

	   		}

	   		game_running = false;

	   	}

      }

    if (ticks % ANIMATION_SPEED ==  0) {
        animate_player();
    }

    draw_player();
    draw_enemies();

    ticks = (ticks + 1);

    if (ticks % 60 == 0) {
    	seconds++;
    	if (seconds == 60) {
    		seconds = 0;
    		minutes++;
    	}
    }
    print_time(minutes, seconds);


}


static XIntc xintc;

static void init_interrupts() {
	XIntc_Initialize(&xintc, XPAR_INTC_0_DEVICE_ID);
	XIntc_Connect (&xintc, XPAR_AXI_INTC_0_VGA_PERIPH_MEM_0_INTR_S_INTR, (XInterruptHandler) vga_interrupt, (void *)0);
	XIntc_Start(&xintc, XIN_REAL_MODE);
	XIntc_Enable(&xintc, XPAR_AXI_INTC_0_VGA_PERIPH_MEM_0_INTR_S_INTR);
	microblaze_enable_interrupts();
}

void reset_function(){

	init_platform();
	init_interrupts();
	init_map();
	init_player();
	init_enemies();
	 ticks = 0;
	 seconds = 0;
	 minutes=0;
	 lives = 3;

}


int main()
{
	reset_function();
	 ticks = 0;
	 seconds = 0;
	 minutes=0;
	 lives = 3;
     init_platform();

    init_interrupts();
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x00, 0x0); // direct mode   0
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0x3); // display_mode  1
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x08, 0x0); // show frame      2
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x0C, 0xff); // font size       3
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0xFFFFFF); // foreground 4
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14,0x008000); // background color 5
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xFF0000); // frame color      6
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x1C, 480); // Set tc
	VGA_PERIPH_MEM_mWriteMemory(XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 1);


	init_platform();
    init_map();
    init_player();
    init_enemies();

    draw_map();
    draw_player();

    draw_sprite(heart_image, 0, MAP_HEIGHT);
    draw_sprite(heart_image, 1, MAP_HEIGHT);
    draw_sprite(heart_image, 2, MAP_HEIGHT);



    draw_sprite(clock_image, 18, MAP_HEIGHT);

    while (get_direction() == DIRECTION_NONE) {

    }

    srand(ticks);

    add_enemy(rand() % (MAP_WIDTH - 2) + 1, rand() % (MAP_HEIGHT - 2) + 1);
    add_enemy(rand() % (MAP_WIDTH - 2) + 1, rand() % (MAP_HEIGHT - 2) + 1);
    add_enemy(rand() % (MAP_WIDTH - 2) + 1, rand() % (MAP_HEIGHT - 2) + 1);

    game_running = true;
    while(1) {

    }


}
