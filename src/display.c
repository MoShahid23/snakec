#include "display.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/ioctl.h>
#include <unistd.h>

static int display_width;
static int display_height;

void display_to_terminal(const char *fmt, int y, int x, ...) {
    va_list args;

    // Move cursor first
    printf("\033[%d;%dH", y + 1, x + 1);

    // Handle variadic args
    va_start(args, x);
    vprintf(fmt, args);
    va_end(args);
}

void display_to_terminal_v(const char *fmt, int y, int x, va_list args) {
    printf("\033[%d;%dH", y + 1, x + 1);
    vprintf(fmt, args);
}

void get_terminal_size(int *cols, int *rows) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        // Failed to get size
        *rows = 25; // Default height
        *cols = 25; // Default width
    }
    else{
        *rows = w.ws_row;
        *cols = w.ws_col;
    }
}

//initialize the display context and terminal grid, and return game logic world size
void display_init(GameConfig *config) {
    //width, height
    int cols, rows;
    //dynamically update game logic area
    get_terminal_size(&cols, &rows);
    config->width = cols;
    config->height = rows - 2;

    //initialize the display context and terminal grid
    display_width = cols;
    display_height = rows - 2;

    printf("\033[?25l"); //hide cursor
}

void display_clear(){
    printf("\033[2J");   //clear screen
}

void display_snake(Snake *snake){
    //display the snake segments on the grid, game running
    for(int i = 0; i < snake->length; i++){
        display_to_terminal("@", snake->segments[i].y, snake->segments[i].x);
    }
}

void display_food(Food *food){
    //display the food item at its position, game runnning
    display_to_terminal("*", food->position.y, food->position.x);
}

void display_score(Score *score){
    //display the current score and high score, game running
    display_to_terminal("Score: %d", display_height, 0, score->score);
}

void display_game_over(Score *score){
    //display the final score and high score
    display_to_terminal("GAME OVER - Final Score: %d\n",
           display_height / 2, display_width / 2 - 10, score->score);

    printf("\033[?25h"); //show cursor
}

void display_log(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    display_to_terminal_v(fmt, display_height + 1, 0, args);
    va_end(args);
}