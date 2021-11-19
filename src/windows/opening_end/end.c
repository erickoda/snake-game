#include <stdio.h>
#include "end.h"

void printScoreText(int snakeLength){
    int score = snakeLength*100;
    char finish;
    printf("Your score was %d\n", score);
    printf("Press any button to finish the program\n");
    scanf(" %c", &finish);
}