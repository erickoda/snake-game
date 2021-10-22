#include <stdio.h>
#include <stdlib.h>
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
            short ehParedeHorizontal = (i == mapInfos->Lines.FirstLine) || (i == mapInfos->Sizes.Height - 1);
            if (ehParedeHorizontal)
            {
                mapBoard[i][j] = HORIZONTAL_WALL;
                continue;
            }

            short ehParedeVertical = (!ehParedeHorizontal) && (j == mapInfos->Lines.FirstColumn || j == mapInfos->Sizes.Length - 1);
            if(ehParedeVertical){
                mapBoard[i][j] = VERTICAL_WALL;
                continue;
            }

            short naoEhParede = !ehParedeHorizontal && !ehParedeVertical;
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

    short nextPositionX = snake->positionX;
    short nextPositionY = snake->positionY;

    switch (newPositionDirection)
    {
        case 'w':
        case 'W':
            nextPositionY -= 1;
            break;

        case 's':
        case 'S':
            nextPositionY += 1;
            break;

        case 'a':
        case 'A':
            nextPositionX -= 1;
            break;

        case 'd':
        case 'D':
            nextPositionX += 1;
            break;
    }

    short nextPositionIsValid = !(verifyNextPosition(map, nextPositionX, nextPositionY, HORIZONTAL_WALL) 
                                || verifyNextPosition(map, nextPositionX, nextPositionY, VERTICAL_WALL));

    if(nextPositionIsValid){
        map[snake->positionY][snake->positionX] = EMPTY_SPACE;
        map[nextPositionY][nextPositionX] = SNAKE;

        snake->positionX = nextPositionX;
        snake->positionY = nextPositionY;
    }
}

void changeFoodPosition(char **map, Position *food, Position *snake, Map mapInfos){

    short snakeHasEaten = (snake->positionX == food->positionX) && (snake->positionY == food->positionY);
    if(snakeHasEaten){
        food->positionX = randowInicialPosition(mapInfos.Sizes.Length - 1 - 1);
        food->positionY = randowInicialPosition(mapInfos.Sizes.Height - 1 - 1);
        map[food->positionY][food->positionX] = FOOD;

        score++;
    }
}

short verifyNextPosition(char **map, short nextPositionX, short nextPositionY, char nextChar){

    short nextPositionChar = map[nextPositionY][nextPositionX] == nextChar;
    if(nextPositionChar){
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