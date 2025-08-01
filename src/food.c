#include "food.h"

void food_init(Food *food, const char *name, int x, int y, int value) {
    //initialize food with arguments
    food->position.x = x;
    food->position.y = y;
    food->value = value;
}

bool food_eaten(Food *food, Snake *snake){
    //check if snake and food positions match, return true/false
    if (snake->segments[0].x == food->position.x &&
        snake->segments[0].y == food->position.y) {
        return true;
    }
    return false;
}