#include "../headers/lib.h"
#include "../headers/board.h"
#include <time.h>

void createBoard(int x, int y, struct Tile board[][MAX_SIZE])
{
    srand(time(NULL));
    int r;

    // all of the border tiles of our board are filled with 0 fish (which is needed for checking if the penguin can move later)
    for (int i = 0; i < y + 2; i++)
    {
        board[i][0] = createTile(i, 0, 0);
        board[i][x + 1] = createTile(i, x + 1, 0);
    }
    for (int i = 0; i < x + 2; i++)
    {
        board[0][i] = createTile(0, i, 0);
        board[y + 1][i] = createTile(y + 1, i, 0);
    }

    // creating the board itself, which is visible to the players
    for (int i = 1; i <= y; i++)
    {
        for (int j = 1; j <= x; j++)
        {
            r = rand() % 4;                    // randomly generating number of fish on the board (1-3)
            board[i][j] = createTile(i, j, r); // creating a tile, i = x coordinates, j = y coordinates
        }
    }
}
struct Tile createTile(int y, int x, int fish)
{
    struct Tile temp;
    temp.y = y;
    temp.x = x;
    temp.fish = fish;
    temp.player = 0;
    temp.isFree = true;
    temp.isActive = true;
    return temp;
}