/*
 * towerdefence.h
 *
 *  Created on: 25.05.2018.
 *      Author: student
 */

#ifndef TOWERDEFENCE_H_
#define TOWERDEFENCE_H_

void init();
void drawSprite(int in_x, int in_y, int out_x, int out_y, int width, int height);
void drawMap();
void printNum(int row,int column,int num);
void printCoins();
void printCreepNumb();
void moveCreep();
void getDirtPos(int startRow,int startColumn);
void getTowerPos();
char getPressedKey();
void placeTower();
void insertCreep();
void turretOneFire();
void turretTwoFire();
void drawWinLvl();
void drawWon();
void drawEndGame();
bool lvl1();
bool lvl2();


#endif /* TOWERDEFENCE_H_ */
