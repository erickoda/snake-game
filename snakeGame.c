#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "map.h"

int main(){

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    /*
        Variables creation and adjustments
    */
    MapSizes mapSizes;
    mapSizes.Length = 10;
    mapSizes.Height = 10;
    short mapFirstLine = 0;
    short mapFirstColumn = 0;

    Position *snake;
    snake = (Position *) malloc(sizeof(Position)*(mapSizes.Length-2)*(mapSizes.Height-2));
    snake[0].positionX = randowInicialPosition(mapSizes.Length - 1 - 1);
    snake[0].positionY = randowInicialPosition(mapSizes.Length - 1 - 1);

    Position food;
    food.positionX = randowInicialPosition(mapSizes.Length - 1 - 1);
    food.positionY = randowInicialPosition(mapSizes.Height - 1 - 1);

    char **map;
    map = (char **) malloc(mapSizes.Length*sizeof(char));
    allocMap(map, mapSizes);

    /*
        Program Starts here
    */
    createMap(map, mapSizes, mapFirstLine, mapFirstColumn);
    
    while(1){
        updateMap(map, food, snake);
        printMap(map, mapSizes);
        updateSnakePosition(snake);
    }

    free(map);
    return 0;
}