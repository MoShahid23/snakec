#ifndef CONTROLLER_H
#define CONTROLLER_H

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT,
    DIR_NONE
} Direction;

void controller_attach();
void controller_detach();
Direction controller_input();

#endif