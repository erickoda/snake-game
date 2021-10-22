#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "map.h"

int score;

int main(){

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));


    /*
        Variables creation and adjustments
    */
    Map firstMapInfos;
    firstMapInfos.Sizes.Height = 10;
    firstMapInfos.Sizes.Length = 10;
    firstMapInfos.Lines.FirstColumn = 0;
    firstMapInfos.Lines.FirstLine = 0;

    Position *snake;
    snake = (Position *) malloc(sizeof(Position)*(firstMapInfos.Sizes.Length-2)*(firstMapInfos.Sizes.Height-2));
    randowCharacterPosition(snake, firstMapInfos);

    Position food;
    randowCharacterPosition(&food, firstMapInfos);

    char **mapBoard;
    mapBoard = (char **) malloc(firstMapInfos.Sizes.Length*sizeof(char));
    allocMap(mapBoard, firstMapInfos);


    /*
        Program Starts here
    */
    createMapBoard(mapBoard, &firstMapInfos);
    addCharactersToMap(mapBoard, food, snake);

    while(1){
        printMap(mapBoard, firstMapInfos);
        snakeNextPosition(mapBoard, snake);
        changeFoodPosition(mapBoard, &food, snake, firstMapInfos);
        upSnakeLength(mapBoard, snake);
    }


    /*
        Cleaning the program
    */
    for (short i = 0; i < firstMapInfos.Sizes.Height; i++)
    {
        free(mapBoard[i]);
    }
    free(mapBoard);
    free(snake);
    return 0;
}

//Tentar fzer um "histórico" de posição da cobra