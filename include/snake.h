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
    int x_velocity; //positive or negative
    int y_velocity;
    bool collided;
} Snake;

void snake_init(Snake *snake, GameConfig *config);
void set_snake_velocity(Snake *snake, int x_velocity, int y_velocity);
void set_snake_length(Snake *snake, int length, bool append);
void snake_move(Snake *snake, GameConfig *config);
bool snake_collision(Snake *snake);

#endif