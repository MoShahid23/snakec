#include "display.h"
#include <stdlib.h>

static DisplayContext display_context;

void display_init(int width, int height) {
    //initialize the display context and terminal grid
    display_context.width = width;
    display_context.height = height;
    display_context.grid = malloc(height * sizeof(char *));
}

void display_clear(){
    //clear the display grid
}

void display_snake(Snake *snake){
    //display the snake segments on the grid, game running
}

void display_food(Food *food){
    //display the food item at its position, game runnning
}

void display_score(Score *score){
    //display the current score and high score, game running
}

void display_game_over(Score *score){
    //display the final score and high score
}
