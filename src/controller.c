#include "controller.h"
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <stdbool.h>
#include <stdio.h>

static struct termios orig_termios;

static void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void controller_attach() {
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void controller_detach() {
    restore_terminal();
}

static bool kbhit() {
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

Direction controller_input() {
    if (kbhit()) {
        char c = getchar();
        if (c == 27) { // Arrow keys
            if (kbhit()) getchar(); // skip [
            if (kbhit()) {
                c = getchar();
                switch (c) {
                    case 'A': return DIR_UP;
                    case 'B': return DIR_DOWN;
                    case 'C': return DIR_RIGHT;
                    case 'D': return DIR_LEFT;
                }
            }
        } else {
            switch (c) {
                case 'w': return DIR_UP;
                case 's': return DIR_DOWN;
                case 'a': return DIR_LEFT;
                case 'd': return DIR_RIGHT;
            }
        }
    }
    return DIR_NONE;
}