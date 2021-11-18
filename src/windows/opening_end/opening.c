#include <stdio.h>
#include "opening.h"

void printOpeningTitle(){
    printf("=======================\n");
    printf("|Welcome to Snake Game|\n");
    printf("=======================\n\n");
}

int chooseGameDifficulty(){
    const int gameDifficulty;
    printf("Choose the difficulty you will play?\n");
    printf("(1) Easy\n");
    printf("(2) Normal\n");
    printf("(3) Hard\n");
    scanf("%d", &gameDifficulty);

    return gameDifficulty;
}