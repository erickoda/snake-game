#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"

extern int score;  

void allocMap(char **map, Map mapInfos){
    for (short i = 0; i < mapInfos.Sizes.Length; i++)
    {
        map[i] = (char *) malloc(mapInfos.Sizes.Height*sizeof(char));
    }
}

void createMapBoard(char **mapBoard, Map *mapInfos){

    for (short i = 0; i < mapInfos->Sizes.Length; i++)
    {
        for (short j = 0; j < mapInfos->Sizes.Height; j++)
        {
            bool ehParedeHorizontal = (i == mapInfos->Lines.FirstLine) || (i == mapInfos->Sizes.Height - 1);
            if (ehParedeHorizontal)
            {
                mapBoard[i][j] = HORIZONTAL_WALL;
                continue;
            }

            bool ehParedeVertical = (!ehParedeHorizontal) && (j == mapInfos->Lines.FirstColumn || j == mapInfos->Sizes.Length - 1);
            if(ehParedeVertical){
                mapBoard[i][j] = VERTICAL_WALL;
                continue;
            }

            bool naoEhParede = !ehParedeHorizontal && !ehParedeVertical;
            if (naoEhParede)
            {
                mapBoard[i][j] = EMPTY_SPACE;
                continue;
            }
        }
    }
}

void addCharactersToMap(char **map, Position food, Position *snake){
    map[food.positionY][food.positionX] = FOOD;
    map[snake[0].positionY][snake[0].positionX] = SNAKE;
}

void snakeNextPosition(char **map, Position *snake){

    static char newPositionDirection;
    scanf(" %c", &newPositionDirection);

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

    short nextPositionIsValid = !( verifyNextPosition(map, next, HORIZONTAL_WALL) 
                                || verifyNextPosition(map, next, VERTICAL_WALL) 
                                || verifyNextPosition(map, next, SNAKE));

    if(nextPositionIsValid){
        map[snake->positionY][snake->positionX] = EMPTY_SPACE;
        map[next.positionY][next.positionX] = SNAKE;

        for (int i = 8*8 - 1; i > 0; i--)
        {
            snake[i].positionX = snake[i-1].positionX;
            snake[i].positionY = snake[i-1].positionY;
        }

        snake->positionX = next.positionX;
        snake->positionY = next.positionY;
    }
}

void changeFoodPosition(char **map, Position *food, Position *snake, Map mapInfos){

    bool snakeHasEaten = (snake->positionX == food->positionX) && (snake->positionY == food->positionY);
    if(snakeHasEaten){
        food->positionX = randowInicialPosition(mapInfos.Sizes.Length - 1 - 1);
        food->positionY = randowInicialPosition(mapInfos.Sizes.Height - 1 - 1);
        map[food->positionY][food->positionX] = FOOD;

        score++;
    }
}

void growSnakeLength(char **map, Position *snake){
    for (int i = 8*8; i >=0; i--)
    {   
        if(i <= score){
            map[snake[i].positionY][snake[i].positionX] = SNAKE;
        }else{
            map[snake[i].positionY][snake[i].positionX] = EMPTY_SPACE;
        }
    }
}

short verifyNextPosition(char **map, Position next, char nextChar){

    bool nextPositionIsChar = map[next.positionY][next.positionX] == nextChar;
    if(nextPositionIsChar){
        return 1;
    } else {
        return 0;
    }
}

void printMap(char **map, Map mapInfos){
    for (int i = 0; i < mapInfos.Sizes.Length; i++)
    {
        for (int j = 0; j < mapInfos.Sizes.Height; j++)
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
    character->positionX = randowInicialPosition(mapInfos.Sizes.Length - 1 - 1);
    character->positionY = randowInicialPosition(mapInfos.Sizes.Length - 1 - 1);
}