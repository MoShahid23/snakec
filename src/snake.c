#include "snake.h"
#include <math.h>

void snake_init(Snake *snake, GameConfig *config){
    //snake starts with 1 segment, stationary at (0,0)
    snake->segments[0].x = config->width / 2;
    snake->segments[0].y = config->height / 2;
    snake->length = 1;
    snake->x_velocity = 0;
    snake->y_velocity = 0;
    snake->collided = false;
}

void set_snake_velocity(Snake *snake, int x_velocity, int y_velocity) {
    //set the snake's velocity from arguments
    snake->x_velocity = x_velocity;
    snake->y_velocity = y_velocity;
}

void set_snake_length(Snake *snake, int length, bool append) {
    //set the snake's velocity from arguments
    if (length > 0){
        if(append){
            snake->length += length;
        } else {
            snake->length = length;
        }
    }
}

void snake_move(Snake *snake, GameConfig *config) {
    snake->collided = false;
    Position start_head_pos = {snake->segments[0].x, snake->segments[0].y};

    //should move normally if only 1 axis has velocity
    snake->segments[0].x += snake->x_velocity;
    snake->segments[0].y += snake->y_velocity;

    //update snake position based on velocity
    for (int i = snake->length - 1; i > 0; i--) {
        snake->segments[i] = snake->segments[i - 1];
        //body still following previous head pos, not new one.
        if(i == 1) {
            snake->segments[i].x = start_head_pos.x;
            snake->segments[i].y = start_head_pos.y;
        }

        if(snake->segments[i].x == snake->segments[0].x &&
           snake->segments[i].y == snake->segments[0].y) {
            //if the head collides with any body segment
            snake->collided = true;
        }
    }

    if(snake->segments[0].x >= config->width){
        snake->segments[0].x = 0; //wrap around horizontally
    }
    if(snake->segments[0].x < 0){
        snake->segments[0].x = config->width-1; //wrap around horizontally
    }
    if(snake->segments[0].y >= config->height){
        snake->segments[0].y = 0; //wrap from up to down
    }
    if(snake->segments[0].y < 0){
        snake->segments[0].y = config->height-1; //wrap from down to up
    }
}

bool snake_collision(Snake *snake){
    return snake->collided;
}