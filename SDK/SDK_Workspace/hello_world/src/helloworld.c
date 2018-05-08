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


#define TOWERU '1'
#define TOWERD '2'
#define GRASS 'G'
#define DIRTPREVIOUS 'P'
#define DIRT 'D'
#define BUSH 'B'
#define CREEP 'C'
#define NUMOFTOWERS 8
#define NUMOFBUSHES 20
#define LAKE1 '3'
#define LAKE2 '4'
#define LAKE3 '5'
#define LAKE4 '6'
#define LAKE5 '7'
#define LAKE6 '8'
#define SPOT 'S'
#define SELECTEDSPOT 'X'


int i, x, y, ii, oi, R, G, B, RGB, kolona, red, RGBgray;
int randomCounter = 50;

char map[SIZEROW][SIZECOLUMN];
int res = 0;
int rowFields[7]={5,5,3,10,10,7,5};
int columnFields[7]={3,5,7,9,12,14,17};
int currentI = 0;
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

//function that generates random game map
/*void makeMap() {


}*/



//extracting pixel data from a picture for printing out on the display

void drawSprite(int in_x, int in_y, int out_x, int out_y, int width, int height) {
	int ox, oy, oi, iy, ix, ii;
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
	int row,column;
	for (row = 0; row < SIZEROW; row++) {
		for (column = 0; column < SIZECOLUMN; column++) {
			if (map1[row][column] == CREEP){
				map1[row][column] = DIRTPREVIOUS;
				if(map1[row+1][column]==DIRT){
					map1[row+1][column]= CREEP;
				}
				if(map1[row-1][column]==DIRT){
					map1[row-1][column]= CREEP;
				}
				if(map1[row][column+1]==DIRT){
					map1[row][column+1]= CREEP;
				}
				if(map1[row][column-1]==DIRT){
					map1[row][column-1]= CREEP;
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

			return 0;
			}
		}
	}
}


int main() {
	int row, column;

	init_platform();
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
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x14, 0x0000FF); // background color 5
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x18, 0xFF0000); // frame color      6
	VGA_PERIPH_MEM_mWriteMemory(
			XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + 0x20, 1);

	//black background
	/*for (x = 0; x < 640; x++) {
		for (y = 0; y < 480; y++) {
			i = y * 640 + x;
			VGA_PERIPH_MEM_mWriteMemory(
					XPAR_VGA_PERIPH_MEM_0_S_AXI_MEM0_BASEADDR + GRAPHICS_MEM_OFF
							+ i * 4, 0x000000);
		}
	}*/


	//drawing a map
	while(1){
		for (row = 0; row < SIZEROW; row++) {
			for (column = 0; column < SIZECOLUMN; column++) {
				//drawSprite(48, 0, 0, 0, 16,32);
				//if(column == 3)
				if (map1[row][column] == GRASS){
					drawSprite(16, 0, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == DIRT || map1[row][column]==DIRTPREVIOUS) {
					drawSprite(0, 0, column * 16, row * 16, 16, 16);
				}
				/*if (map1[row][column] == TOWERU) {
					drawSprite(32, 0, column * 16, row * 16, 16, 16);
				}*/
				/*if (map1[row][column] == TOWERD) {
					drawSprite(32, 16, column * 16, row * 16, 16, 16);
				}*/
				if (map1[row][column] == BUSH){
					drawSprite(32, 0, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == CREEP){
					drawSprite(48, 0, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == LAKE1){
					drawSprite(0, 16, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == LAKE2){
					drawSprite(16, 16, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == LAKE3){
					drawSprite(32, 16, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == LAKE4){
					drawSprite(0, 32, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == LAKE5){
					drawSprite(16, 32, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == LAKE6){
					drawSprite(32, 32, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == SPOT){
					drawSprite(64, 0, column * 16, row * 16, 16, 16);
				}
				if (map1[row][column] == SELECTEDSPOT){
					drawSprite(64, 16, column * 16, row * 16, 16, 16);
				}

				if (map1[row][column] == TOWERU){
					drawSprite(64,32,column*16,row*16,16,16);
				}








			}




		}

					if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & RIGHT) == 0){
						if(currentI<6){
						if(map1[rowFields[currentI]][columnFields[currentI]] != TOWERU){
													map1[rowFields[currentI]][columnFields[currentI]] = SPOT;
						}
						currentI++;
						map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDSPOT;
						}

					}


					if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & LEFT) == 0){
						if(currentI>0){
						if(map1[rowFields[currentI]][columnFields[currentI]] != TOWERU){
							map1[rowFields[currentI]][columnFields[currentI]] = SPOT;
						}
						currentI--;
						map1[rowFields[currentI]][columnFields[currentI]] = SELECTEDSPOT;
						}
						}
					if((Xil_In32(XPAR_MY_PERIPHERAL_0_BASEADDR) & CENTER) == 0){
						map1[rowFields[currentI]][columnFields[currentI]] = TOWERU;
					}

		drawMap();
		//cleanup_platform();
	}


	return 0;
}
