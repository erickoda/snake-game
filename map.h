#ifndef MAP_HEADER_FILE_H
#define MAP_HEADER_FILE_H

#define HORIZONTAL_WALL '-'
#define VERTICAL_WALL '|'
#define EMPTY_SPACE ' '
#define SNAKE '@'
#define FOOD '*'

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

typedef struct
{
    short FirstLine;
    short FirstColumn;

} MapLines;

typedef struct
{

    MapSizes Sizes;
    MapLines Lines;

}Map;


void allocMap(char **map, Map mapInfos);
void createMapBoard(char **mapBoard, Map *mapInfos);
void addCharactersToMap(char **map, Position food, Position *snake);
void snakeNextPosition(char **map, Position *snake);
short verifyNextPosition(char **map, Position next, char nextChar);
void changeFoodPosition(char **map, Position *food, Position *snake, Map mapInfos);
void printMap(char **map, Map mapInfos);
short randowInicialPosition(short maxPosition);
void randowCharacterPosition(Position *character, Map mapInfos);
void upSnakeLength(char **map, Position *snake);

#endif