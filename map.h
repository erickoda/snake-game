#ifndef MAP_HEADER_FILE_H
#define MAP_HEADER_FILE_H

#define HORIZONTAL_WALL '-'
#define VERTICAL_WALL '|'

typedef struct
{
    short positionX;
    short positionY;

} Position;

typedef struct
{
    short Length;
    short Height;

} MapSizes;

void allocMap(char **map, MapSizes mapSizes);
void createMapBoard(char **map, MapSizes mapSizes, short mapFirstLine, short mapFirstColumn);
void addCharactersToMap(char **map, Position food, Position *snake);
void snakeNextPosition(char **map, Position *snake, MapSizes mapSizes, Position food);
short verifyNextPosition(char **map, short nextPositionX, short nextPositionY, char nextChar);
void changeFoodPosition(char **map, Position *food, Position *snake, MapSizes mapSizes);
void printMap(char **map, MapSizes mapSizes);
short randowInicialPosition(short maxPosition);

#endif