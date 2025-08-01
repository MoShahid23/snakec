#include "snake.h"
#include "food.h"
#include "score.h"
#include "display.h"
#include "controller.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define FRAME_TIME_MS 80

void sleep_frame(struct timespec start) {
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);

    long elapsed_ms = (end.tv_sec - start.tv_sec) * 1000 +
                      (end.tv_nsec - start.tv_nsec) / 1000000;

    if (elapsed_ms < FRAME_TIME_MS) {
        usleep((FRAME_TIME_MS - elapsed_ms) * 1000);
    }
}

int main(){
    //game configuration, display context for now
    GameConfig config;
    display_init(&config);

    printf("Welcome to Snake Game!\n");
    Snake snake;
    Food food;
    Score score;

    snake_init(&snake, &config);
    food_init(&food, "Apple", 10, 10, 1);
    score_init(&score);

    bool game_running = true;
    controller_attach();
    while (game_running)
    {
        struct timespec start;
        clock_gettime(CLOCK_MONOTONIC, &start);

        //handling input
        //if blocks ensure snake does not reverse direction into itself
        Direction dir = controller_input();
        switch (dir){
            case DIR_UP:
                if(snake.y_velocity <= 0){
                    set_snake_velocity(&snake, 0, -1);
                }
                break;
            case DIR_DOWN:
                if(snake.y_velocity >= 0){
                    set_snake_velocity(&snake, 0, 1);
                }
                break;
            case DIR_LEFT:
                if(snake.x_velocity <= 0){
                    set_snake_velocity(&snake, -1, 0);
                }
                break;
            case DIR_RIGHT:
                if(snake.x_velocity >= 0){
                    set_snake_velocity(&snake, 1, 0);
                }
                break;
            default:
                break;
        }

        snake_move(&snake, &config);

        if(food_eaten(&food, &snake)) {
            score_update(&score, food.value);
            set_snake_length(&snake, food.value, true);
            food_init(&food, "Apple", rand() % config.width, rand() % config.height, 1);
        }

        if(snake_collision(&snake)) {
            game_running = false;
            display_game_over(&score);
            controller_detach();
        } else {
            display_clear();
            display_log("x:%d, y:%d", snake.segments[0].x, snake.segments[0].y);
            display_snake(&snake);
            display_food(&food);
            display_score(&score);
            fflush(stdout);
        }

        sleep_frame(start);
    }

    return 0;
}
