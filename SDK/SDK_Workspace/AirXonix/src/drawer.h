#ifndef DRAWER_H
#define DRAWER_H

#include <stdint.h>

#define INVISIBLE_COLOR 0xFF00FF

void draw_sprite(const uint32_t *sprite, int x, int y);
void undraw_sprite(int x, int y);
void delete_heart(int x, int y);

#endif
