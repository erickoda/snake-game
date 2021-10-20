#include <stdio.h>
#include <stdlib.h>
#include "map.h"

void allocMap(char **map, MapSizes mapSizes){
    for (short i = 0; i < mapSizes.Length; i++)
    {
        map[i] = (char *) malloc(mapSizes.Height*sizeof(char));
    }
}

void createMap(char **map, MapSizes mapSizes, short mapFirstLine, short mapFirstColumn){

    for (short i = 0; i < mapSizes.Length; i++)
    {
        for (short j = 0; j < mapSizes.Height; j++)
        {
            short ehParedeHorizontal = (i == mapFirstLine) || (i == mapSizes.Height - 1);
            if (ehParedeHorizontal)
            {
                map[i][j] = '-';
                continue;
            }

            short ehParedeVertical = (!ehParedeHorizontal) && (j == mapFirstColumn || j == mapSizes.Length - 1);
            if(ehParedeVertical){
                map[i][j] = '|';
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

void updateMap(char **map, Position food, Position *snake){
    map[food.positionY][food.positionX] = '*';
    map[snake[0].positionY][snake[0].positionX] = '@';
}

void updateSnakePosition(Position *snake){

    static char newPositionDirection;
    scanf(" %c", &newPositionDirection);
    switch (newPositionDirection)
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