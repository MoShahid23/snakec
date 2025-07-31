#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "gameconfig.h"

typedef struct {
    int x, y;
} Position;

typedef struct {
    Position segments[100];
    int length;
    int x_velocity; //positive ir negative
    int y_velocity;
} Snake;

void snake_init(Snake *snake);
void set_snake_velocity(Snake *snake, int x_velocity, int y_velocity);
void snake_move(Snake *snake, GameConfig *config);
bool snake_collision(const Snake *snake);

#endif