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
    short mapFirstLine = 0;
    short mapFirstColumn = 0;
    MapSizes mapSizes;
    mapSizes.Length = 10;
    mapSizes.Height = 10;

    Position *snake;
    snake = (Position *) malloc(sizeof(Position)*(mapSizes.Length-2)*(mapSizes.Height-2));
    snake[0].positionX = randowInicialPosition(mapSizes.Length - 1 - 1);
    snake[0].positionY = randowInicialPosition(mapSizes.Length - 1 - 1);

    Position food;
    food.positionX = randowInicialPosition(mapSizes.Length - 1 - 1);
    food.positionY = randowInicialPosition(mapSizes.Height - 1 - 1); //Tentar tornar food global

    char **map;
    map = (char **) malloc(mapSizes.Length*sizeof(char));
    allocMap(map, mapSizes);


    /*
        Program Starts here
    */
    createMapBoard(map, mapSizes, mapFirstLine, mapFirstColumn);
    addCharactersToMap(map, food, snake);

    while(1){
        printMap(map, mapSizes);
        snakeNextPosition(map, snake, mapSizes, food);
        changeFoodPosition(map, &food, snake, mapSizes);
    }


    /*
        Cleaning the program
    */
    for (short i = 0; i < mapSizes.Height; i++)
    {
        free(map[i]);
    }
    free(map);
    free(snake);
    return 0;
}