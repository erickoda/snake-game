#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "map.h"

int main(){

    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    Position *snake;
    Position food;
    MapSizes mapSizes;
    short mapFirstLine = 0;
    short mapFirstColumn = 0;

    mapSizes.Length = 10;
    mapSizes.Height = 10;
    food.positionX = randowInicialPosition(mapSizes.Length - 1 - 1);
    food.positionY = randowInicialPosition(mapSizes.Height - 1 - 1);

    char **map;
    map = (char **) malloc(mapSizes.Length*sizeof(char));
    allocMap(map, mapSizes);

    createMap(map, mapSizes, mapFirstLine, mapFirstColumn);
    updateMap(map, food);
    printMap(map, mapSizes);

    free(map);
    return 0;
}