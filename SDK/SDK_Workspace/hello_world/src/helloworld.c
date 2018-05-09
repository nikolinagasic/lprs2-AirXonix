/*
 * Copyright (c) 2009-2012 Xilinx, Inc.  All rights reserved.
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 *
 *
 *
 */

#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xio.h"
#include "xil_exception.h"
#include "vga_periph_mem.h"
#include "towerdefence_sprites.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "maps.h"

#define UP 0b01000000
#define DOWN 0b00000100
#define LEFT 0b00100000
#define RIGHT 0b00001000
#define CENTER 0b00010000
#define SW0 0b00000001
#define SW1 0b00000010

#define GRASS 'G'
#define DIRTPREVIOUS 'P'
#define DIRT 'D'
#define BUSH 'B'
#define LAKE1 '1'
#define LAKE2 '2'
#define LAKE3 '3'
#define LAKE4 '4'
#define LAKE5 '5'
#define LAKE6 '6'
#define HP1 '7'
#define HP2 '8'
#define HP3 '9'
#define HP4 '0'
#define CREEP 0
#define CREEP1 1
#define CREEP2 2
#define CREEP3 3
#define CREEP4 4
#define MOVEDCREEP 'c'
#define SPOT 'S'
#define SELECTEDSPOT 'X'
#define TOWER 'T'
#define TOWER2 't'
#define SELECTEDTOWER 'O'
#define SELECTEDTOWER2 'o'

bool endGame = false;
int rowFields[7]={5,5,3,10,10,7,5};
int columnFields[7]={3,5,7,9,12,14,17};
int currentI = 0;
int btnCnt = 0;
int currentHP = 3;
void init(){
	VGA_PERIPH_MEM_mWriteMemory(
				XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x00, 0x0); // direct mode   0
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x04, 0x3); // display_mode  1
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x08, 0x0); // show frame      2
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x0C, 0xff); // font size       3
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x10, 0xFFFFFF); // foreground 4
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14,0x008000); // background color 5
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xFF0000); // frame color      6
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 1);
}

//extracting pixel data from a picture for printing out on the display
void drawSprite(int in_x, int in_y, int out_x, int out_y, int width, int height) {
	int x, y, ox, oy, oi, iy, ix, ii, R, G, B, RGB;
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			ox = out_x + x;
			oy = out_y + y;
			oi = oy * 320 + ox;
			ix = in_x + x;
			iy = in_y + y;
			ii = iy * towerdefence_sprites.width + ix;
			R = towerdefence_sprites.pixel_data[ii
					* towerdefence_sprites.bytes_per_pixel] >> 5;
			G = towerdefence_sprites.pixel_data[ii
					* towerdefence_sprites.bytes_per_pixel + 1] >> 5;
			B = towerdefence_sprites.pixel_data[ii
					* towerdefence_sprites.bytes_per_pixel + 2] >> 5;
			R <<= 6;
			G <<= 3;
			RGB = R | G | B;

			VGA_PERIPH_MEM_mWriteMemory(
					XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + GRAPHICS_MEM_OFF
							+ oi * 4 , RGB);
		}
	}
}

void drawMap(){
	int row, column;
	for (row = 0; row < SIZEROW; row++) {
		for (column = 0; column < SIZECOLUMN; column++) {
			if(mapChanges[row][column]){
				mapChanges[row][column] = false;
				if (map1[row][column] == GRASS){
					drawSprite(16, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == DIRT || map1[row][column] == DIRTPREVIOUS) {
					drawSprite(0, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == BUSH){
					drawSprite(32, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP){
					drawSprite(48, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP1){
					drawSprite(48, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP2){
					drawSprite(48, 32, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP3){
					drawSprite(48, 48, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == CREEP4){
					drawSprite(48, 64, column * 16, row * 16, 16, 16);

				}
				else if (map1[row][column] == LAKE1){
					drawSprite(0, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE2){
					drawSprite(16, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE3){
					drawSprite(32, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE4){
					drawSprite(0, 32, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE5){
					drawSprite(16, 32, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == LAKE6){
					drawSprite(32, 32, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == SPOT){
					drawSprite(64, 0, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == SELECTEDSPOT){
					drawSprite(64, 16, column * 16, row * 16, 16, 16);
				}
				else if (map1[row][column] == TOWER){
					drawSprite(80,48,column*16,row*16,16,16);
				}
				else if (map1[row][column] == TOWER2){
					drawSprite(96,48,column*16,row*16,16,16);
				}
				else if(map1[row][column] == SELECTEDTOWER){
					drawSprite(80,64,column*16,row*16,16,16);
				}
				else if(map1[row][column] == SELECTEDTOWER2){
					drawSprite(96,64,column*16,row*16,16,16);
				}
				else if(map1[row][column] == HP1){
					drawSprite(112,0,column*16,row*16,16,16);
				}
				else if(map1[row][column] == HP2){
					drawSprite(112,16,column*16,row*16,16,16);
				}
				else if(map1[row][column] == HP3){
					drawSprite(112,32,column*16,row*16,16,16);
				}
				else if(map1[row][column] == HP4){
					drawSprite(112,48,column*16,row*16,16,16);
				}


			}
		}
	}
}

void moveCreep(){

	int row, column;
	int i = 0;
	int pom[10];
	int x[10],y[10];
	for (row = 0; row < SIZEROW; row++) {
		for (column = 0; column < SIZECOLUMN; column++) {
			if (map1[row][column] == CREEP4){
				map1[row][column] = DIRT;
				mapChanges[row][column] = true;
				
				if (map1[row + 1][column] == DIRTPREVIOUS) {
					map1[row + 1][column] = DIRT;
				}

				if (map1[row - 1][column] == DIRTPREVIOUS) {
					map1[row - 1][column] = DIRT;
				}

				if (map1[row][column + 1] == DIRTPREVIOUS) {
					map1[row][column + 1] = DIRT;
				}

				if (map1[row][column - 1] == DIRTPREVIOUS) {
					map1[row][column - 1] = DIRT;
				}
			}

			else if (map1[row][column] == CREEP ||map1[row][column] == CREEP1 ||map1[row][column] == CREEP2 ||map1[row][column] == CREEP3){
				pom[i] = map1[row][column];

				map1[row][column] = DIRTPREVIOUS;
				if(map1[row+1][column]==DIRT){
					map1[row+1][column]= MOVEDCREEP;
					mapChanges[row+1][column]= true;
					x[i] = row+1;
					y[i++] = column;
				}
				if(map1[row-1][column]==DIRT){
					map1[row-1][column]= MOVEDCREEP;
					mapChanges[row-1][column]= true;
					x[i] = row-1;
					y[i++] = column;
				}
				if(map1[row][column+1]==DIRT){
					map1[row][column+1]= MOVEDCREEP;
					mapChanges[row][column+1]= true;
					x[i] = row;
					y[i++] = column+1;
				}
				if(map1[row][column-1]==DIRT){
					map1[row][column-1]= MOVEDCREEP;
					mapChanges[row][column-1]= true;
					x[i] = row;
					y[i++] = column-1;
				}
				if(map1[row+1][column]==DIRTPREVIOUS){
					map1[row+1][column]= DIRT;

				}
				if(map1[row-1][column]==DIRTPREVIOUS){
					map1[row-1][column]= DIRT;
				}
				if(map1[row][column+1]==DIRTPREVIOUS){
					map1[row][column+1]= DIRT;
				}
				if(map1[row][column-1]==DIRTPREVIOUS){
					map1[row][column-1]= DIRT;
				}
				if(row == 14 || column == 19){
					map1[row][column] = DIRT;
					currentHP--;
					if(currentHP == 2){
						map1[5][19] = HP2;
						map1[7][19] = HP2;
						mapChanges[5][19] = true;
						mapChanges[7][19] = true;
					}
					else if(currentHP == 1){
						map1[5][19] = HP3;
						map1[7][19] = HP3;
						mapChanges[5][19] = true;
						mapChanges[7][19] = true;
					}
					else if(currentHP == 0){
						map1[5][19] = HP4;
						map1[7][19] = HP4;
						mapChanges[5][19] = true;
						mapChanges[7][19] = true;
						endGame = true;
					}
				}
				mapChanges[row][column] = true;


			}
		}
	}
	int j;
	for (j=0;j<i;j++){
		map1[x[j]][y[j]] = pom[j];
	}
	drawMap();
}



void placeTower(){
	if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & RIGHT) == 0){
		if(currentI<6){
			if(map1[rowFields[currentI]][columnFields[currentI]] != TOWER &&
					map1[rowFields[currentI]][columnFields[currentI]] != SELECTEDTOWER &&
					map1[rowFields[currentI]][columnFields[currentI]] != TOWER2 &&
										map1[rowFields[currentI]][columnFields[currentI]] != SELECTEDTOWER2){
				map1[rowFields[currentI]][columnFields[currentI]] = SPOT;
			}
			else{
				if(map1[rowFields[currentI]][columnFields[currentI]] == SELECTEDTOWER){
					map1[rowFields[currentI]][columnFields[currentI]] = TOWER;
				}
				else{
					map1[rowFields[currentI]][columnFields[currentI]] = TOWER2;
				}
			}

			mapChanges[rowFields[currentI]][columnFields[currentI]] = true;
			currentI++;
			if(map1[rowFields[currentI]][columnFields[currentI]] != TOWER &&
					map1[rowFields[currentI]][columnFields[currentI]] != TOWER2){
				map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDSPOT;
			}
			else{
				if(map1[rowFields[currentI]][columnFields[currentI]] == TOWER){
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER;
				}
				else{
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
				}
			}
		}
	}
	if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & LEFT) == 0){
		if(currentI>0){
			if(map1[rowFields[currentI]][columnFields[currentI]] != TOWER &&
					map1[rowFields[currentI]][columnFields[currentI]] != SELECTEDTOWER &&
				map1[rowFields[currentI]][columnFields[currentI]] != TOWER2 &&
									map1[rowFields[currentI]][columnFields[currentI]] != SELECTEDTOWER2){
				map1[rowFields[currentI]][columnFields[currentI]] = SPOT;
			}
			else{
				if(map1[rowFields[currentI]][columnFields[currentI]] == SELECTEDTOWER){
					map1[rowFields[currentI]][columnFields[currentI]] = TOWER;
				}
				else{
					map1[rowFields[currentI]][columnFields[currentI]] = TOWER2;
				}
			}
			mapChanges[rowFields[currentI]][columnFields[currentI]] = true;
			currentI--;
			if(map1[rowFields[currentI]][columnFields[currentI]] != TOWER &&
					map1[rowFields[currentI]][columnFields[currentI]] != TOWER2){
				map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDSPOT;
			}
			else{
				if(map1[rowFields[currentI]][columnFields[currentI]] == TOWER){
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER;
				}
				else{
					map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
				}
			}
		}
	}
	if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & UP) == 0){
		btnCnt = (btnCnt + 1)%2;
		if(btnCnt==0){
			map1[0][19] = SELECTEDTOWER;
			map1[1][19] = TOWER2;
		}
		else{
			map1[0][19] = TOWER;
			map1[1][19] = SELECTEDTOWER2;
		}
		mapChanges[0][19] = true;
		mapChanges[1][19] = true;
	}


	if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & CENTER) == 0){
		if(map1[rowFields[currentI]][columnFields[currentI]] == SELECTEDSPOT){
			if(btnCnt==0){
				map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER;
			}
			else{
				map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
			}
		}
		else if(map1[rowFields[currentI]][columnFields[currentI]] == SELECTEDTOWER){
			map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDTOWER2;
		}

	}

	mapChanges[rowFields[currentI]][columnFields[currentI]] = true;
	drawMap();
}

void insertCreep(){
	map1[0][2] = CREEP;
	mapChanges[0][2] = true;
	drawMap();
}

void turretOneFire(){
	int row,column;
	for (row = 0; row < SIZEROW; row++) {
		for (column = 0; column < SIZECOLUMN; column++) {
			if((map1[row][column] == TOWER) ){
				int i,j;
				for(i=-1;i<2;i++){
					for(j=-1;j<2;j++){
						if(map1[row+i][column+j] == CREEP || map1[row+i][column+j] == CREEP1 || map1[row+i][column+j] == CREEP2 || map1[row+i][column+j] == CREEP3){
							map1[row+i][column+j]++;
							mapChanges[row+i][column+j]=true;
						}

					}
				}
			}
		}
	}


	drawMap();
}

void drawEndGame(){
	int row,column;
	while(1){
		for (row = 0; row < SIZEROW; row++) {
			for (column = 0; column < SIZECOLUMN; column++) {
				if (gameOver[row][column] == DIRT) {
					drawSprite(0, 0, column * 16, row * 16, 16, 16);
				}
				else if (gameOver[row][column] == CREEP){
					drawSprite(48, 0, column * 16, row * 16, 16, 16);
					gameOver[row][column] = CREEP4;
				}
				else if (gameOver[row][column] == CREEP4){
					drawSprite(48, 64, column * 16, row * 16, 16, 16);
					gameOver[row][column] = CREEP;
				}
			}
		}
		for (row=0;row < 2500000;row++);
	}
}

int main() {
	unsigned int creepTimeCnt = 0;
	int rnd,row,column;
	srand(30);
	int creepCnt = 0;
	init_platform();
	init();
	drawMap(); // init map
	unsigned int i = 0;
		while(1){
			if(endGame){
				/*drawEndGame();
				break;*/
			}
			moveCreep();
			turretOneFire();
			if(creepTimeCnt == rnd){
				insertCreep();
				creepCnt++;
				creepTimeCnt = 0;
				rnd = (rand() % 20) + 5;

			}
			else{
				creepTimeCnt++;
			}

			placeTower();
			for(i=0;i<1500000;i++){
			}

	}

	// cleanup_platform();

	return 0;
}
