#ifndef SCORE_H
#define SCORE_H

typedef struct {
    int score;
    int high_score;
} Score;

//always initialize score to 0
void score_init(Score *score);
//update score based on food eaten
void score_update(Score *score, int value);

#endif