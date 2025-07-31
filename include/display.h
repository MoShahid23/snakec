#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "snake.h"
#include "food.h"
#include "score.h"

typedef struct {
    int width;
    int height;
    char **grid;
} DisplayContext;

void display_init(int width, int height);
void display_clear();
void display_snake(Snake *snake);
void display_food(Food *food);
void display_score(Score *score);
void display_game_over(Score *score);

#endif