#include "../headers/placement.h"

void placementPhase(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[], FILE *fp, char filename[])
{
    int x, y;
    system("cls");
    printf("PLACEMENT PHASE\n");
    printf("Press ENTER to continue");
    getchar();
    // until there are penguins to be placed
    do
    {
        // prints game information
        printf("Player %d turn\n", ptr->currentPlayer);                            // whose turn is it
        printf("Penguins's left: %d\n", players[ptr->currentPlayer].freePenguins); // how many penguins can they place
        showBoard(*ptr, board, players);

        selectPenguin(ptr, board, &players[ptr->currentPlayer]);
        printf("Press ENTER to continue");
        getchar();
        updateFile(*ptr, board, players, fp, filename);
        swapPlayer(ptr);

        system("cls");
    } while (ptr->freePenguins);
}

void selectPenguin(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player *pl)
{
    int sum = 0, maxsum = 0; // calculates sum of the penguins on nearby tiles. The function will place the penguin on the tile with the biggest sum
    int x, y;
    // selecting the ice floe and placing the penguin
    for (int i = 1; i <= ptr->y; i++)
        for (int j = 1; j <= ptr->x; j++)
        {
            sum = 0;
            if (board[i][j].fish == 1 && board[i][j].isFree)
            {
                // if the tile has penguins on all sides select the tile
                if (board[i - 1][j].fish != 0 && board[i][j + 1].fish != 0 && board[i + 1][j].fish != 0 && board[i][j - 1].fish != 0)
                {
                    y = i;
                    x = j;
                    placePenguin(ptr, board, pl, j, i);
                    return; // exit the function as we already placed the penguin
                }

                // else calculate the sum of nearby penguins and the program will select the one with the biggest amount of nearby fish
                else
                {
                    sum += board[i - 1][j].fish + board[i][j + 1].fish + board[i + 1][j].fish + board[i][j - 1].fish;
                    if (sum > maxsum)
                    {
                        maxsum = sum;
                        y = i;
                        x = j;
                    }
                }
            }
        }
    placePenguin(ptr, board, pl, x, y);
}

void placePenguin(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player *pl, int x, int y)
{
    board[y][x].player = ptr->currentPlayer; // updates what player is occupying the floe
    board[y][x].isFree = false;              // updates that the floe is occupied
    pl->score += board[y][x].fish;           // updates score
    board[y][x].fish = 0;                    // removes all fish from the floe
    pl->freePenguins--;                      // reduces the amount of available penguins the player has
    ptr->freePenguins--;                     // reduces the amount of free penguins in the game
}
