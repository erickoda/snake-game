typedef struct
{
    short positionX;
    short positionY;

}Position;

typedef struct
{
    short Length;
    short Height;

} MapSizes;

void allocMap(char **map, MapSizes mapSizes);
void createMap(char **map, MapSizes mapSizes, short mapFirstLine, short mapFirstColumn);
void updateMap(char **map, Position food);
void printMap(char **map, MapSizes mapSizes);
short randowInicialPosition(short maxPosition);