#ifndef FOOD_H
#define FOOD_H

#include "snake.h"
#include <stdbool.h>

typedef struct {
    char item_name[10];
    Position position;
    int value;
} Food;

void food_init(Food *food, const char *name, int x, int y, int value, GameConfig *config);
bool food_eaten(Food *food, Snake *snake);

#endif