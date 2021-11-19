#ifndef MAP_HEADER_FILE_H
#define MAP_HEADER_FILE_H

#define HORIZONTAL_WALL '-'
#define VERTICAL_WALL '|'
#define EMPTY_SPACE ' '
#define SNAKE '0'
#define SNAKE_HEAD '@'
#define FOOD '*'
#define SNAKE_NECK 'O'

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
char getSnakeNextPosition(char **map, Position *snake, char newPositionDirection);
void snakeWalks(Position *snake, char nextPositionDirection);
void snakeTeleports(char **map, Position *snake, char newPositionDirection);
short verifyNextPositionHasChar(char **map, Position next, char nextChar);
void printMap(char **map, Map mapInfos);
short randowInicialPosition(short maxPosition);
void randowCharacterPosition(Position *character, Map mapInfos);
void updateSnakePositionOnMap(char **map, Position *snake, int snakeLength);
void createNewFood(char **map, Position *food, Map mapInfos);
void snakeTeleportsHorizontaly(char **map, Position *snake, char nextPositionDirection);
void snakeTeleportsVerticaly(char **map, Position *snake, char nextPositionDirection);
void changeSnakeBodyPosition(Position *snake);
char getSnakeDirection();

#endif