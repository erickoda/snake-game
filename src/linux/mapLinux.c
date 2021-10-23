#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "mapLinux.h"

#include <sys/select.h>
#include <termios.h>
#include <fcntl.h>

extern int snakeLength;


int _kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

void allocMap(char **map, Map *mapInfos){
    for (short i = 0; i < mapInfos->Sizes.Length; i++)
    {
        map[i] = (char *) malloc(mapInfos->Sizes.Height*sizeof(char));
    }
}

void createMapBoard(char **mapBoard, Map *mapInfos){

    for (short i = 0; i < mapInfos->Sizes.Length; i++)
    {
        for (short j = 0; j < mapInfos->Sizes.Height; j++)
        {
            bool isHorizontalWall = (i == mapInfos->Lines.FirstLine) || (i == mapInfos->Sizes.Height - 1);
            if (isHorizontalWall)
            {
                mapBoard[i][j] = HORIZONTAL_WALL;
                continue;
            }

            bool isVerticalWall = (!isHorizontalWall) && (j == mapInfos->Lines.FirstColumn || j == mapInfos->Sizes.Length - 1);
            if(isVerticalWall){
                mapBoard[i][j] = VERTICAL_WALL;
                continue;
            }

            bool isNotWall = !isHorizontalWall && !isVerticalWall;
            if (isNotWall)
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

bool getSnakeNextPosition(char **map, Position *snake){

    struct termios old_tio, new_tio;
	unsigned char c;

    /* get the terminal settings for stdin */
    tcgetattr(STDIN_FILENO,&old_tio);

    /* we want to keep the old setting to restore them a the end */
    new_tio=old_tio;

    /* disable canonical mode (buffered i/o) and local echo */
    new_tio.c_lflag &=(~ICANON & ~ECHO);

    /* set the new settings immediately */
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

    static char newPositionDirection;

    if(_kbhit()){
        newPositionDirection = getchar();
    }

    Position next;

    next.positionX = snake->positionX;
    next.positionY = snake->positionY;

    switch (newPositionDirection)
    {
        case 'w':
        case 'W':
            next.positionY -= 1;
            break;

        case 's':
        case 'S':
            next.positionY += 1;
            break;

        case 'a':
        case 'A':
            next.positionX -= 1;
            break;

        case 'd':
        case 'D':
            next.positionX += 1;
            break;
        default:
            return true;
    }

    bool nextPositionIsWall  = (verifyNextPosition(map, next, HORIZONTAL_WALL) 
                                || verifyNextPosition(map, next, VERTICAL_WALL));
    bool nextPositionIsSnake = verifyNextPosition(map, next, SNAKE);

    bool nextPositionIsValid = !(nextPositionIsSnake || nextPositionIsWall);

    if(nextPositionIsValid){

        for (int i = 8*8 - 1; i > 0; i--)
        {
            snake[i].positionX = snake[i-1].positionX;
            snake[i].positionY = snake[i-1].positionY;
        }

        snake->positionX = next.positionX;
        snake->positionY = next.positionY;

        return true;
    }

    else if(nextPositionIsWall){
        return true;
    }

    else if(nextPositionIsSnake){
        return true;
    }

    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);

}

void changeFoodPositionAndGrowSnakeLength(char **map, Position *food, Position *snake, Map mapInfos){

    bool snakeHasEaten = (snake->positionX == food->positionX) && (snake->positionY == food->positionY);
    if(snakeHasEaten){

        snakeLength++;

        growSnakeLength(map, snake);

        createNewFood(map, food, mapInfos);
        return;
    }
    growSnakeLength(map, snake);
}

void createNewFood(char **map, Position *food, Map mapInfos){

    randowCharacterPosition(food, mapInfos);

    bool positionHasSnake = map[food->positionY][food->positionX] == SNAKE;
    if(positionHasSnake){
        createNewFood(map, food, mapInfos);
    }

    map[food->positionY][food->positionX] = FOOD;

}

void growSnakeLength(char **map, Position *snake){
    for (int i = 8*8; i > 0; i--)
    {   
        bool isSnake = (i <= snakeLength);
        if(isSnake){
            map[snake[i].positionY][snake[i].positionX] = SNAKE;
        }else if (i = snakeLength+1){
            map[snake[i].positionY][snake[i].positionX] = EMPTY_SPACE; //Clean the old space of the snake
        }
    }
    map[snake[0].positionY][snake[0].positionX] = SNAKE_HEAD;
}

short verifyNextPosition(char **map, Position next, char nextChar){

    bool nextPositionIsChar = map[next.positionY][next.positionX] == nextChar;
    if(nextPositionIsChar){
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