#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void printMap(char **map, int mapLength, int mapHeight);

int main(){

    setlocale(LC_ALL, "Portuguese");

    short mapLength = 10;
    short mapHeight = 10;
    short mapFirstLine = 0;
    short mapFirstColumn = 0;

    char **map;
    map = (char **) malloc(sizeof(char)*mapLength);

    for (int i = 0; i < mapLength; i++)
    {
        map[i] = (char *) malloc(sizeof(char)*mapHeight);
    }

    for (int i = 0; i < mapLength; i++)
    {
        for (int j = 0; j < mapHeight; j++)
        {
            short ehParedeHorizontal = (i == mapFirstLine) || (i == mapHeight - 1);
            if (ehParedeHorizontal)
            {
                map[i][j] = '-';
            }

            short ehParedeVertical = (!ehParedeHorizontal) && (j == mapFirstColumn || j == mapLength - 1);
            if(ehParedeHorizontal){
                map[i][j] = '|';
            }

            short naoEhParede = !ehParedeHorizontal && !ehParedeVertical;
            if (naoEhParede)
            {
                map[i][j] = '@';
            }
        }
    }
    
        // {'-','-','-','-','-','-','-','-','-','-'},
        // {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        // {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        // {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        // {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        // {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        // {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        // {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        // {'|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
        // {'-','-','-','-','-','-','-','-','-','-'},

    printMap(map, mapLength, mapHeight);

    printf("\n");

    free(map);
    return 0;
}

void printMap(char **map, int mapLength, int mapHeight){
    for (int i = 0; i < mapLength; i++)
    {
        for (int j = 0; j < mapHeight; j++)
        {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}