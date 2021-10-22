#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "map.h"

int snakeLength;

int main(){

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));
    bool snakesStillAlive = true;

    /*
        Variables creation and adjustments
    */
    Map firstMapInfos;
    firstMapInfos.Sizes.Height = 10;
    firstMapInfos.Sizes.Length = 10;
    firstMapInfos.Lines.FirstColumn = 0;
    firstMapInfos.Lines.FirstLine = 0;

    Position *snake;
    snake = (Position *) calloc(sizeof(Position),(firstMapInfos.Sizes.Length-2)*(firstMapInfos.Sizes.Height-2));
    randowCharacterPosition(snake, firstMapInfos);

    Position food;
    randowCharacterPosition(&food, firstMapInfos);

    char **mapBoard;
    mapBoard = (char **) malloc(firstMapInfos.Sizes.Length*sizeof(char*));
    allocMap(mapBoard, &firstMapInfos);


    /*
        Program Starts here
    */
    createMapBoard(mapBoard, &firstMapInfos);
    addCharactersToMap(mapBoard, food, snake);

    do{
        printMap(mapBoard, firstMapInfos);
        snakesStillAlive = 
        snakeNextPosition(mapBoard, snake);
        changeFoodPositionAndGrowSnakeLength(mapBoard, &food, snake, firstMapInfos);
    }while(snakesStillAlive);


    /*
        Cleaning the memory
    */
    for (int i = 0; i < firstMapInfos.Sizes.Height; i++)
    {
        free(mapBoard[i]);
    }
    free(mapBoard);
    free(snake);
    return 0;
}