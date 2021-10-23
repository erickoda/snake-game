#include <stdio.h>
#include "end.h"

extern int snakeLength;

void endText(){
    int score = snakeLength*100;
    char finish;
    printf("Your score was %d\n", score);
    printf("Press any button to stop the program\n");
    scanf("%c", &finish);
}