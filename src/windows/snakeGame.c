#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <Windows.h>

#include "./map/map.h"
#include "./opening_end/opening.h"
#include "./opening_end/end.h"

Map firstMapInfos;

int updateGameDificulty(int gameDifficulty, int snakeLength);

int main(){

    srand(time(NULL));

    /*
        Variables creation and adjustments
    */
   
    bool snakesStillsAlive = true;
    int snakeLength = 0;

    firstMapInfos.Sizes.Height = 15;
    firstMapInfos.Sizes.Width = 15;
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
    float speed;
    int won = false;
    char nextPositionChar;
    char snakeDirection;
    bool hasEaten = false;

    createMapBoard(mapBoard, &firstMapInfos);
    addCharactersToMap(mapBoard, &food, snake);

    do{
        system("cls");
        printMap(mapBoard, firstMapInfos);
        speed = updateGameDificulty(gameDifficulty, snakeLength);

        snakeDirection = getSnakeDirection();
        nextPositionChar = getSnakeNextPosition(mapBoard, snake, snakeDirection);

        // updateSnakePositionOnMap(mapBoard, snake, snakeLength);

        if (nextPositionChar == HORIZONTAL_WALL || nextPositionChar == VERTICAL_WALL)
            snakeTeleports(mapBoard, snake, snakeDirection);

        if (nextPositionChar == EMPTY_SPACE)
            snakeWalks(snake, snakeDirection);
        
        if (nextPositionChar == FOOD){
            snakeWalks(snake, snakeDirection);
            snakeLength++;
            hasEaten = true;
        }

        if (nextPositionChar == SNAKE)
            snakesStillsAlive = false;

        updateSnakePositionOnMap(mapBoard, snake, snakeLength);

        if(hasEaten){
            createNewFood(mapBoard, &food, firstMapInfos); // -> Gambiarra -> pensar em um jeito de melhorar iiso ak
            hasEaten = false;
        }

        if(snakeLength == (firstMapInfos.Sizes.Height-1-1)*(firstMapInfos.Sizes.Width-1-1) - 1){
            won = true;
        }
        
        Sleep(speed); // gameDifficulty++; //TODO acrescentar a speed -> if ((score % 2 == 0) && snakeHasEaten)

    }while(snakesStillsAlive && !won);

    printScoreText(snakeLength);


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

int updateGameDificulty(int gameDifficulty, int snakeLength){

    static int speedCoefficient;
    int speed;

    if (snakeLength % 10 == 0)
        speedCoefficient += 1;

    speed = 200.0 / gameDifficulty + speedCoefficient;

    return speed;
}