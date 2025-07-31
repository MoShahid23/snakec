#include "snake.h"
#include "food.h"
#include "score.h"
#include "display.h"
#include <stdlib.h>

int main(){
    printf("Welcome to Snake Game!\n");
    GameConfig config = {100, 100};
    Snake snake;
    Food food;
    Score score;

    snake_init(&snake);
    food_init(&food, "Apple", rand() % config.width, rand() % config.height, 1, &config);
    score_init(&score);
    display_init(config.width, config.height);

    bool game_running = true;

    while (game_running)
    {
        snake_move(&snake, &config);

        if(food_eaten(&food, &snake)) {
            score_update(&score, &food);
            food_init(&food, "Apple", rand() % config.width, rand() % config.height, 1, &config);
        }

        if(snake_collision(&snake)) {
            game_running = false;
            display_game_over(&score);
        } else {
            display_clear();
            display_snake(&snake);
            display_food(&food);
            display_score(&score);
        }
    }

    return 0;
}
