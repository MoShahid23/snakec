#include "score.h"

void score_init(Score *score){
    //initialize scores to 0
    score->score = 0;
    score->high_score = 0;
}

void score_update(Score *score, int value){
    //update score based on food eaten
    score->score += value;
}