#include "../headers/gamecont.h"

void contPlace(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[], int pengNr)
{
    ptr->penguinNr = pengNr;                    // number of penguins available to each player
    ptr->freePenguins = ptr->playerNr * pengNr; // number of free penguins on the board
    for (int i = 1; i <= ptr->playerNr; i++)
    {
        players[i].freePenguins = pengNr; // number of free penguins belonging to the player
        players[i].penguinNr = pengNr;    // number of penguins
    }
    placementPlayer(ptr, board, players);
    fillEdges(ptr->x, ptr->y, board);
}

void contMove(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[])
{
    ptr->penguinNr = 0;     // number of penguins available to each player
    ptr->freePenguins = 0;  // number of free penguins on the board
    ptr->currentPlayer = 1; // sets the player's number (i.e if this program goes second change value to two)
    for (int i = 1; i <= ptr->playerNr; i++)
    {
        players[i].freePenguins = 0; // number of player's free penguins
        players[i].penguinNr = 0;    // number of player's penguins
    }
    fillEdges(ptr->x, ptr->y, board);
    for (int i = 1; i <= ptr->y; i++)
        for (int j = 1; j <= ptr->x; j++)
        {
            // if there is a player on the board, increase amount of penguins (on the board and belonging to the player)
            if (board[i][j].player != 0)
            {
                ptr->freePenguins++;
                players[board[i][j].player].freePenguins++;
                players[board[i][j].player].penguinNr++;
                board[i][j].isFree = false; // flags the tile as occupied
            }
        }
    ptr->penguinNr = players[1].penguinNr;
    canMove(board, players, ptr);
}

void placementPlayer(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[])
{
    for (int i = 1; i <= ptr->y; i++)
        for (int j = 1; j <= ptr->x; j++)
            // if there is a player reduce amount of penguins in the phase and belonging to the player
            if (board[i][j].player != 0)
            {
                players[board[i][j].player].freePenguins--;
                ptr->freePenguins--;
            }

    int pl = 1; // the player with the least placed penguins is the current player
    for (int i = 1; i < ptr->playerNr; i++)
        if (players[i + 1].freePenguins > players[i].freePenguins)
            pl = i + 1;
    ptr->currentPlayer = pl;
}

void fillEdges(int x, int y, struct Tile board[][MAX_SIZE])
{
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
}