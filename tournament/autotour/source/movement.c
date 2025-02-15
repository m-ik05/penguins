#include "../headers/movement.h"

void movementPhase(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[], FILE *fp, char filename[])
{
    struct Tile selected;

    system("cls");
    // we increase the number of free penguins as they were reduced to 0 in placement phase and make all tiles active again (so that they can be properly vetted once again)
    for (int i = 1; i <= ptr->playerNr; i++)
    {
        players[i].freePenguins = ptr->penguinNr;
    }
    for (int i = 1; i <= ptr->y; i++)
        for (int j = 1; j <= ptr->x; j++)
            board[i][j].isActive = true;

    ptr->freePenguins = ptr->penguinNr * ptr->playerNr;
    canMove(board, players, ptr); // checks if any of the penguins that were placed in placement phase are blocked

    movePenguin(ptr, board, selected, players);
    printf("Press ENTER to continue");
    getchar();
    updateFile(*ptr, board, players, fp, filename);
}

void movePenguin(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Tile temp, struct Player players[])
{
    int x, y;
    int pl = ptr->currentPlayer;

    system("cls");
    // prints game information
    printf("Player %d turn\n", pl);                                   // who's turn is it
    printf("Player's penguins left: %d\n", players[pl].freePenguins); // how many the penguin the player has left
    printf("Penguins left in the game: %d\n", ptr->freePenguins);     // how many penguins on the board can move
    printf("Player's left in the game: ");                            // how many player's can still move
    for (int i = 1; i <= ptr->playerNr; i++)
        if (players[i].freePenguins != 0)
            printf("%d ", i);
    printf("\n");
    showBoard(*ptr, board, players);

    // selects the penguin to move
    for (int i = 1; i <= ptr->y; i++)
        for (int j = 1; j <= ptr->x; j++)
        {
            if (board[i][j].player == pl && board[i][j].isActive)
            {
                y = i;
                x = j;
                goto jump;
            }
        }
jump:
    struct Tile moved = makeMove(x, y, board);
    board[moved.y][moved.x].player = pl;               // updates what player is occupying the floe
    board[moved.y][moved.x].isFree = false;            // updates that the floe is occupied
    players[pl].score += board[moved.y][moved.x].fish; // updates current player's score
    board[moved.y][moved.x].fish = 0;                  // removes all fish from the floe
    board[y][x].player = 0;                            // updates that the floe has no players on it
    board[y][x].isFree = true;                         // updates that the ice floe is free

    canMove(board, players, ptr); // checks if the player can move the penguin after it moved
}

struct Tile makeMove(int x, int y, struct Tile board[][MAX_SIZE])
{
    struct Tile temp; // temporary structure that allow us to return the coordinates
    int max = 0, dir; // maximal amount of moves, which direction to move
    int up = 0;       // number of moves up
    int right = 0;    // number of moves right
    int down = 0;     // number of moves down
    int left = 0;     // number of moves left

    int i, j;
    for (int k = 1; k <= 4; k++)
    {
        i = y;
        j = x;
        board[y][x].fish++; // temporarily increase the amount of fish on the tile so that the tile function can actually work
        while (board[i][j].fish != 0)
        {
            switch (k)
            {
            case 1:
                i--; // moves up (decreases y coordinates)
                up++;
                if (up > max)
                {
                    max = up;
                    dir = k;
                }
                break;
            case 2:
                j++; // moves right (increases x coordinates)
                right++;
                if (right > max)
                {
                    max = right;
                    dir = k;
                }
                break;
            case 3:
                i++; // moves down (increases y coordinates)
                down++;
                if (down > max)
                {
                    max = down;
                    dir = k;
                }
                break;
            case 4:
                j--; // moves left (decreases x coordinates)
                left++;
                if (down > max)
                {
                    max = down;
                    dir = k;
                }
                break;
            }
        }
        board[y][x].fish--;
    }
    switch (dir)
    {
    case 1: // if the most amount of moves will be up
        temp.x = x;
        temp.y = y - 1;
        break;
    case 2: // if the most amount of moves will be right
        temp.x = x + 1;
        temp.y = y;
        break;
    case 3: // if the most amount of moves will be down
        temp.x = x;
        temp.y = y + 1;
        break;
    case 4: // if the most amount of moves will be left
        temp.x = x - 1;
        temp.y = y;
        break;
    }
    return temp;
}