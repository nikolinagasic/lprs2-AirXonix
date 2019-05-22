#include "map.h"
#include "drawer.h"
#include "enemy.h"

#include <stdint.h>

uint32_t empty_tile[TILE_SIZE * TILE_SIZE] = {
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915,
    0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300, 0x7F3300,
    0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915, 0x7F3300, 0xA87915
};

uint32_t filled_tile[TILE_SIZE * TILE_SIZE] = {
    0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060,
    0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080,
    0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060,
    0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080,
    0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060,
    0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080,
    0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060,
    0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080,
    0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060,
    0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080,
    0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060,
    0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080,
    0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060,
    0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080,
    0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060,
    0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080, 0x606060, 0x808080
};
uint32_t clock_image[TILE_SIZE * TILE_SIZE] = {
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0x000000, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0x000000, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000,
    0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0x000000, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFF00FF,
    0xFF00FF, 0xFF00FF, 0xFF00FF};

uint32_t heart_image[TILE_SIZE * TILE_SIZE] = {
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFF1E47, 0xFF1E47,
    0x000000, 0x000000, 0x000000, 0xFF1E47, 0xFF1E47, 0xFF00FF, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0x000000, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFF1E47, 0xFF1E47, 0xFF1D4C, 0xFF1E47, 0xFF1E47,
    0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47,
    0x000000, 0x000000, 0x000000, 0x000000, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1D49, 0xFF1E47, 0xFF1E47, 0xFF1E47,
    0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47,0x000000, 0x000000, 0x000000, 0x000000, 0xFF1E47,
    0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47,
    0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47,0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFF1E47,
    0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47,
    0xFF1E47, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0xFF1E47, 0xFF1E47, 0xFF1E47, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000,0xFF1E47, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000};
uint32_t black_image[TILE_SIZE * TILE_SIZE] = {
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
    0x000000, 0x000000, 0x000000};




uint32_t dashed_tile[TILE_SIZE * TILE_SIZE];
uint8_t map[MAP_HEIGHT * MAP_WIDTH];

TileType tile_at(int x, int y) {
    return map[y * MAP_WIDTH + x];
}

void set_tile(int x, int y, TileType type) {
    map[y * MAP_WIDTH + x] = type;
}

void init_map(void) {
    int i;
    int j;

    for (i = 0; i < MAP_WIDTH; i++) {
        for (j = 0; j < MAP_HEIGHT; j++) {
            if (i == 0 || j == 0 || i == MAP_WIDTH - 1 || j == MAP_HEIGHT - 1) {
                map[j * MAP_WIDTH + i] = TILE_FILLED;
            }
            else {
                map[j * MAP_WIDTH + i] = TILE_EMPTY;
            }
        }
    }

    for (i = 0; i < TILE_SIZE; i++) {
        for (j = 0; j < TILE_SIZE; j++) {
            if (i < TILE_SIZE / 3 || i > 2 * TILE_SIZE / 3 || j < TILE_SIZE / 3 || j > 2 * TILE_SIZE / 3) {
                dashed_tile[j * TILE_SIZE + i] = INVISIBLE_COLOR;
            }
            else {
                dashed_tile[j * TILE_SIZE + i] = 0xCCFFCC;
            }
        }
    }
}

void draw_map(void) {
    int i;
    int j;

    for (i = 0; i < MAP_WIDTH; i++) {
        for (j = 0; j < MAP_HEIGHT; j++) {

            if (tile_at(i, j) == TILE_FILLED) {
                draw_sprite(filled_tile, i, j);
            }
            else {
                draw_sprite(empty_tile, i, j);
            }
        }
        //dole liniju gde su srca pravi crno van srca
        draw_sprite(black_image, i, MAP_HEIGHT);
    }
}


void check_fill(void) {
    int i;
    int j;
    int clear_inner = 0;
    int clear_outer = 0;
    for (j = 1; j < MAP_HEIGHT - 1; j++) {
        enum TileType previous_type = TILE_FILLED;
        int p = 0;
        for (i = 1; i < MAP_WIDTH - 1; i++) {
            enum TileType type = tile_at(i, j);

            if (type == TILE_EMPTY && previous_type == TILE_DASHED) {
                p = !p; //p se aktivira kada predjemo isprekidanu
            }

            previous_type = type;
//kad naidjemo na dashed nista ne radimo
            if (type == TILE_EMPTY) {
                if (p) {
                	//kada se p aktivira tj predje dashed
                    set_tile(i, j, TILE_MAYBE_FILLED_INNER);
                }
                else {
                    set_tile(i, j, TILE_MAYBE_FILLED_OUTER);
                }
            }

        }
    }
    // u kom delu se nalaze neprijatelji

    for (i = 0; i < enemy_count; i++) {
        if (tile_at(enemies[i].x, enemies[i].y) == TILE_MAYBE_FILLED_INNER) {
            clear_inner = 1;
        }
        else if (tile_at(enemies[i].x, enemies[i].y) == TILE_MAYBE_FILLED_OUTER) {
            clear_outer = 1;
        }
    }
//popunjava i nepop

    for (j = 1; j < MAP_HEIGHT - 1; j++) {
        for (i = 1; i < MAP_WIDTH - 1; i++) {
            const enum TileType tile = tile_at(i, j);

            if (tile == TILE_DASHED) {
                set_tile(i, j, TILE_FILLED);
                draw_sprite(filled_tile, i, j);
            }
            else if (tile == TILE_MAYBE_FILLED_INNER) {
                if (clear_inner) {
                    set_tile(i, j, TILE_EMPTY);
                }
                else {
                    set_tile(i, j, TILE_FILLED);
                    draw_sprite(filled_tile, i, j);
                }
            }
            else if (tile == TILE_MAYBE_FILLED_OUTER) {
                if (clear_outer) {
                    set_tile(i, j, TILE_EMPTY);
                }
                else {
                    set_tile(i, j, TILE_FILLED);
                    draw_sprite(filled_tile, i, j);
                }
            }
        }
    }
}
