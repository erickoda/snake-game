#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "map.h"

extern int snakeLength;  
const extern Map firstMapInfos;

void allocMap(char **map, Map *mapInfos){
    for (short i = 0; i < mapInfos->Sizes.Height; i++)
    {
        map[i] = (char *) malloc(mapInfos->Sizes.Width*sizeof(char));
    }
}

void createMapBoard(char **mapBoard, Map *mapInfos){

    for (short i = 0; i < mapInfos->Sizes.Height; i++)
    {
        for (short j = 0; j < mapInfos->Sizes.Width; j++)
        {
            bool isHorizontalWall = (i == mapInfos->Lines.FirstLine) || (i == mapInfos->Sizes.Height - 1);
            if (isHorizontalWall)
            {
                mapBoard[i][j] = HORIZONTAL_WALL;
                continue;
            }

            bool isVerticalWall = (!isHorizontalWall) && (j == mapInfos->Lines.FirstColumn || j == mapInfos->Sizes.Width - 1);
            if(isVerticalWall){
                mapBoard[i][j] = VERTICAL_WALL;
                continue;
            }

            bool isNotWall = !isHorizontalWall && !isVerticalWall;
            if (isNotWall)
            {
                mapBoard[i][j] = EMPTY_SPACE;
                continue;
            }
        }
    }
}

void addCharactersToMap(char **map, const Position *food, const Position *snake){
    map[food->positionY][food->positionX] = FOOD;
    map[snake->positionY][snake->positionX] = SNAKE;
}

bool getSnakeNextPosition(char **map, Position *snake){

    static char newPositionDirection;

    if(_kbhit()){
        newPositionDirection = getch();
    }

    Position next;

    next.positionX = snake->positionX;
    next.positionY = snake->positionY;

    switch (newPositionDirection)
    {
        case 'w':
        case 'W':
            next.positionY -= 1;
            break;

        case 's':
        case 'S':
            next.positionY += 1;
            break;

        case 'a':
        case 'A':
            next.positionX -= 1;
            break;

        case 'd':
        case 'D':
            next.positionX += 1;
            break;
        default:
            return true;
    }

    bool nextPositionIsWall  = (verifyNextPositionHasChar(map, next, HORIZONTAL_WALL)
                                || verifyNextPositionHasChar(map, next, VERTICAL_WALL));
    bool nextPositionIsSnake = verifyNextPositionHasChar(map, next, SNAKE);

    bool nextPositionIsValid = !(nextPositionIsSnake || nextPositionIsWall);

    if(nextPositionIsValid){

        changeSnakeBodyPosition(snake);

        snake->positionX = next.positionX;
        snake->positionY = next.positionY;

        return true;
    }

    if(nextPositionIsWall){

        changeSnakeBodyPosition(snake);

        snakeTeleports(map, snake, next);   
        return true;
    }

    if(nextPositionIsSnake){
        return false;
    }
}

void changeSnakeBodyPosition(Position *snake){

    for (int i = (firstMapInfos.Sizes.Height-1-1)*(firstMapInfos.Sizes.Width-1-1) - 1; i > 0; i--)
    {
        snake[i].positionX = snake[i-1].positionX;
        snake[i].positionY = snake[i-1].positionY;
    }
}

void snakeTeleports(char **map, Position *snake, Position next){
    
    bool nextPositionIsHorizontal_TopWall = verifyNextPositionHasChar(map, next, HORIZONTAL_WALL) && (next.positionY == firstMapInfos.Lines.FirstLine);
    if(nextPositionIsHorizontal_TopWall){
        snake->positionY = firstMapInfos.Sizes.Height-1-1;
        return;
    }
    bool nextPositionIsHorizontal_BottomWall = verifyNextPositionHasChar(map, next, HORIZONTAL_WALL) && (next.positionY == firstMapInfos.Sizes.Height-1);
    if(nextPositionIsHorizontal_BottomWall){
        snake->positionY = firstMapInfos.Lines.FirstLine + 1;
        return;
    }

    bool nextPositionIsVertical_RightWall = verifyNextPositionHasChar(map, next, VERTICAL_WALL) && (next.positionX == firstMapInfos.Lines.FirstLine);
    if(nextPositionIsVertical_RightWall){
        snake->positionX = firstMapInfos.Sizes.Width-1-1;
        return;
    }
    bool nextPositionIsVertical_LeftWall = verifyNextPositionHasChar(map, next, VERTICAL_WALL) && (next.positionX == firstMapInfos.Sizes.Width-1);
    if(nextPositionIsVertical_LeftWall){
        snake->positionX = firstMapInfos.Lines.FirstLine + 1;
        return;
    }
}

void changeFoodPositionAndGrowSnakeLength(char **map, Position *food, Position *snake, Map mapInfos){ // Todo -> dps de tirar a fn growSnakeLength daqui, trocar o nome da fn

    bool snakeHasEaten = (snake->positionX == food->positionX) && (snake->positionY == food->positionY);
    if(snakeHasEaten){

        snakeLength++;

        growSnakeLength(map, snake); //Todo -> provavelmente eu posso deixar essa fn no main, já que ela é involvada independentemente de qlqr coisa 

        createNewFood(map, food, mapInfos);
        return;
    }
    growSnakeLength(map, snake);
}

void createNewFood(char **map, Position *food, Map mapInfos){

    randowCharacterPosition(food, mapInfos);

    bool positionHasSnake = map[food->positionY][food->positionX] == SNAKE;
    if(positionHasSnake){
        createNewFood(map, food, mapInfos);
    }

    map[food->positionY][food->positionX] = FOOD;

}

void growSnakeLength(char **map, Position *snake){ //Todo -> change this fn name -> this fn dont really change the snake length -> this fn update the snake body position in the map
    for (int i = snakeLength + 1; i >= 0; i--)
    {   
        bool isSnake = (i <= snakeLength);
        if(isSnake){
            map[snake[i].positionY][snake[i].positionX] = SNAKE;
        }else {
            map[snake[i].positionY][snake[i].positionX] = EMPTY_SPACE; //Clean the old space of the snake
        }
    }
    map[snake->positionY][snake->positionX] = SNAKE_HEAD;
}

short verifyNextPositionHasChar(char **map, Position next, char nextChar){

    bool nextPositionIsChar = map[next.positionY][next.positionX] == nextChar;
    if(nextPositionIsChar){
        return 1;
    } else {
        return 0;
    }
}

void printMap(char **map, Map mapInfos){
    for (int i = 0; i < mapInfos.Sizes.Height; i++)
    {
        for (int j = 0; j < mapInfos.Sizes.Width; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

short randowInicialPosition(short maxPosition){
    return rand() % maxPosition + 1;
}

void randowCharacterPosition(Position *character, Map mapInfos){
    character->positionX = randowInicialPosition(mapInfos.Sizes.Width - 1 - 1);
    character->positionY = randowInicialPosition(mapInfos.Sizes.Height - 1 - 1);
}