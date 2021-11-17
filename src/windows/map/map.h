#ifndef MAP_HEADER_FILE_H
#define MAP_HEADER_FILE_H

#define HORIZONTAL_WALL '-'
#define VERTICAL_WALL '|'
#define EMPTY_SPACE ' '
#define SNAKE '@'
#define SNAKE_HEAD 'O'
#define FOOD '*'

typedef struct
{
    int positionX;
    int positionY;

} Position;

typedef struct
{
    int Width;
    int Height;

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


void allocMap(char **map, Map *mapInfos);
void createMapBoard(char **mapBoard, Map *mapInfos);
void addCharactersToMap(char **map, const Position *food, const Position *snake);
bool getSnakeNextPosition(char **map, Position *snake);
short verifyNextPosition(char **map, Position next, char nextChar);
void changeFoodPositionAndGrowSnakeLength(char **map, Position *food, Position *snake, Map mapInfos);
void printMap(char **map, Map mapInfos);
short randowInicialPosition(short maxPosition);
void randowCharacterPosition(Position *character, Map mapInfos);
void growSnakeLength(char **map, Position *snake);
void createNewFood(char **map, Position *food, Map mapInfos);
void snakeTeleports(char **map, Position *snake, Position next);
void changeSnakeBodyPosition(Position *snake);

#endif