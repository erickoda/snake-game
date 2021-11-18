#include <stdio.h>
#include "end.h"

extern int snakeLength;

void printScoreText(){
    int score = snakeLength*100;
    char finish;
    printf("Your score was %d\n", score);
    printf("Press any button to finish the program\n");
    scanf(" %c", &finish);
}