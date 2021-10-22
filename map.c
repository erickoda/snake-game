#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void allocMap(char **map, MapSizes mapSizes){
    for (short i = 0; i < mapSizes.Length; i++)
    {
        map[i] = (char *) malloc(mapSizes.Height*sizeof(char));
    }
}

void createMapBoard(char **map, MapSizes mapSizes, short mapFirstLine, short mapFirstColumn){

    for (short i = 0; i < mapSizes.Length; i++)
    {
        for (short j = 0; j < mapSizes.Height; j++)
        {
            short ehParedeHorizontal = (i == mapFirstLine) || (i == mapSizes.Height - 1);
            if (ehParedeHorizontal)
            {
                map[i][j] = HORIZONTAL_WALL;
                continue;
            }

            short ehParedeVertical = (!ehParedeHorizontal) && (j == mapFirstColumn || j == mapSizes.Length - 1);
            if(ehParedeVertical){
                map[i][j] = VERTICAL_WALL;
                continue;
            }

            short naoEhParede = !ehParedeHorizontal && !ehParedeVertical;
            if (naoEhParede)
            {
                map[i][j] = ' ';
                continue;
            }
        }
    }
}

void addCharactersToMap(char **map, Position food, Position *snake){
    map[food.positionY][food.positionX] = '*';
    map[snake[0].positionY][snake[0].positionX] = '@';
}

void snakeNextPosition(char **map, Position *snake, MapSizes mapSizes, Position food){

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
        map[snake->positionY][snake->positionX] = ' ';
        map[nextPositionY][nextPositionX] = '@';

        snake->positionX = nextPositionX;
        snake->positionY = nextPositionY;
    }

}

void changeFoodPosition(char **map, Position *food, Position *snake, MapSizes mapSizes){

    short snakeHasEaten = (snake->positionX == food->positionX) && (snake->positionY == food->positionY);
    if(snakeHasEaten){
        food->positionX = randowInicialPosition(mapSizes.Length - 1 - 1);
        food->positionY = randowInicialPosition(mapSizes.Height - 1 - 1);
        map[food->positionY][food->positionX] = '*';
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

void printMap(char **map, MapSizes mapSizes){
    for (int i = 0; i < mapSizes.Length; i++)
    {
        for (int j = 0; j < mapSizes.Height; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

short randowInicialPosition(short maxPosition){
    return rand() % maxPosition + 1;
}