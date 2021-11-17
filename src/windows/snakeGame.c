#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>

#include "./map/map.h"
#include "./opening_end/opening.h"
#include "./opening_end/end.h"

Map firstMapInfos;
int snakeLength;

int main(){

    srand(time(NULL));
    bool snakesStillsAlive = true;


    /*
        Variables creation and adjustments
    */
    firstMapInfos.Sizes.Height = 15;
    firstMapInfos.Sizes.Width = 30;
    firstMapInfos.Lines.FirstColumn = 0;
    firstMapInfos.Lines.FirstLine = 0;

    Position *snake;
    snake = (Position *) calloc(sizeof(Position),(firstMapInfos.Sizes.Width-2)*(firstMapInfos.Sizes.Height-2));
    randowCharacterPosition(snake, firstMapInfos);

    Position food;
    randowCharacterPosition(&food, firstMapInfos);

    char **mapBoard;
    mapBoard = (char **) malloc(firstMapInfos.Sizes.Height*sizeof(char*));
    allocMap(mapBoard, &firstMapInfos);


    /*
        Program Starts here
    */
    printOpeningTitle();
    int gameDifficulty = chooseGameDifficulty();
    int won = false;

    createMapBoard(mapBoard, &firstMapInfos);
    addCharactersToMap(mapBoard, &food, snake);

    do{
        system("cls");
        printMap(mapBoard, firstMapInfos);
        snakesStillsAlive = 
        getSnakeNextPosition(mapBoard, snake);
        changeFoodPositionAndGrowSnakeLength(mapBoard, &food, snake, firstMapInfos);
        Sleep(gameDifficulty*33);

        if(snakeLength == (firstMapInfos.Sizes.Height-1-1)*(firstMapInfos.Sizes.Width-1-1) - 1){
            won = true;
        }

    }while(snakesStillsAlive && !won);

    printScoreText();


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