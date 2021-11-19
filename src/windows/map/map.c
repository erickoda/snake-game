#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include "map.h"
 
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
    map[snake->positionY][snake->positionX] = SNAKE_HEAD;
}

char getSnakeDirection(){

    static char newPositionDirection = 'w';

    if(_kbhit()){
        newPositionDirection = getch();
    }

    return newPositionDirection;
}

char getSnakeNextPosition(char **map, Position *snake, char newPositionDirection){ //TODO -> change this fn name -> getSnakeNextPositionChar

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
    }

    bool nextPositionIsHorizontalWall  = verifyNextPositionHasChar(map, next, HORIZONTAL_WALL);
    bool nextPositionIsVerticalWall = verifyNextPositionHasChar(map, next, VERTICAL_WALL);
    bool nextPositionIsSnake = verifyNextPositionHasChar(map, next, SNAKE);
    bool nextPositionIsEmpty = verifyNextPositionHasChar(map, next, EMPTY_SPACE);
    bool nextPositionIsFood = verifyNextPositionHasChar(map, next, FOOD);

    if (nextPositionIsVerticalWall)
        return VERTICAL_WALL;

    if (nextPositionIsHorizontalWall)
        return HORIZONTAL_WALL;

    if (nextPositionIsSnake)
        return SNAKE;
    
    if(nextPositionIsEmpty)
        return EMPTY_SPACE;

    if(nextPositionIsFood)
        return FOOD;
}

void snakeWalks(Position *snake, char nextPositionDirection){

    changeSnakeBodyPosition(snake);

    switch (nextPositionDirection)
    {
        case 'w':
        case 'W':
            snake->positionY -= 1;
            break;

        case 's':
        case 'S':
            snake->positionY += 1;
            break;

        case 'a':
        case 'A':
            snake->positionX -= 1;
            break;

        case 'd':
        case 'D':
            snake->positionX += 1;
            break;
    }
}

void snakeTeleports(char **map, Position *snake, char nextPositionDirection){

    changeSnakeBodyPosition(snake);
    
    if (nextPositionDirection == 'w' || nextPositionDirection == 'W' || nextPositionDirection == 's' || nextPositionDirection == 'S'){
        snakeTeleportsHorizontaly(map, snake, nextPositionDirection);
        return;
    }

    if (nextPositionDirection == 'a' || nextPositionDirection == 'A' || nextPositionDirection == 'd' || nextPositionDirection == 'D')
        snakeTeleportsVerticaly(map, snake, nextPositionDirection);
}

void snakeTeleportsHorizontaly(char **map, Position *snake, char nextPositionDirection){
    
    bool nextPositionIsHorizontal_TopWall = nextPositionDirection == 'w' || nextPositionDirection == 'W';
    if(nextPositionIsHorizontal_TopWall){
        snake->positionY = firstMapInfos.Sizes.Height-1-1;
        return;
    }

    bool nextPositionIsHorizontal_BottomWall = nextPositionDirection == 's' || nextPositionDirection == 'S';
    if(nextPositionIsHorizontal_BottomWall){
        snake->positionY = firstMapInfos.Lines.FirstLine + 1;
        return;
    }
}

void snakeTeleportsVerticaly(char **map, Position *snake, char nextPositionDirection){

    bool nextPositionIsVertical_RightWall = nextPositionDirection == 'a' || nextPositionDirection == 'A';
    if(nextPositionIsVertical_RightWall){
        snake->positionX = firstMapInfos.Sizes.Width-1-1;
        return;
    }

    bool nextPositionIsVertical_LeftWall = nextPositionDirection == 'd' || nextPositionDirection == 'D';
    if(nextPositionIsVertical_LeftWall){
        snake->positionX = firstMapInfos.Lines.FirstLine + 1;
        return;
    }
}

void createNewFood(char **map, Position *food, Map mapInfos){

    randowCharacterPosition(food, mapInfos);

    bool positionHasSnake = map[food->positionY][food->positionX]    == SNAKE 
                            || map[food->positionY][food->positionX] == SNAKE_HEAD 
                            || map[food->positionY][food->positionX] == SNAKE_NECK;
    if(positionHasSnake){
        createNewFood(map, food, mapInfos);
    }

    map[food->positionY][food->positionX] = FOOD;

}

void updateSnakePositionOnMap(char **map, Position *snake, int snakeLength){
    for (int i = snakeLength + 1; i >= 0; i--)
    {   
        bool isSnake = (i <= snakeLength);
        if(isSnake){
            if(i == 1){
                map[snake[i].positionY][snake[i].positionX] = SNAKE_NECK;
                continue;
            }
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
        return true;
    } else {
        return false;
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

void changeSnakeBodyPosition(Position *snake){

    for (int i = (firstMapInfos.Sizes.Height-1-1)*(firstMapInfos.Sizes.Width-1-1) - 1; i > 0; i--)
    {
        snake[i].positionX = snake[i-1].positionX;
        snake[i].positionY = snake[i-1].positionY;
    }
}