#include "../headers/general.h"

void showBoard(struct Game tempGame, struct Tile board[][MAX_SIZE], struct Player players[])
{
    int x = tempGame.x;
    int y = tempGame.y;
    int i, j;

    // shows the upper edges of the board that the players cannot move on(x coordinates and upper game board borders)
    printf("   ");
    for (j = 1; j <= x; j++)
    {
        printf("%2d ", j);
    }
    printf("\n");
    printf("  ");
    for (j = 1; j <= x; j++)
    {
        printf("---");
    }
    printf("\n");

    for (i = 1; i <= y; i++)
    {
        for (j = 0; j <= x; j++)
        {
            // shows the left edges of the board (y coordinates and left game border)
            if (j < 1 && i < 10)
                printf("%d |", i);
            else if (j < 1 && i >= 10)
                printf("%d|", i);
            // shows the playable part of the board
            else
            {
                if (board[i][j].player != 0) // if there is a player on the ice floe
                    printf(" P%d", board[i][j].player);
                else if (board[i][j].fish == 0) // if there are no fishes on the ice floe
                    printf("   ");
                else // if the ice floe has fish but no players
                    printf(" %d ", board[i][j].fish);
            }
        }
        printf("\n");
    }
    // shows player score
    for (int i = 1; i <= tempGame.playerNr; i++)
        printf("Player's %d score: %d\n", i, players[i].score);
}

void takeFish(struct Player *pl, int fish)
{
    pl->score += fish; // updates player's score
}

void swapPlayer(struct Game *pl)
{
    if (pl->currentPlayer == pl->playerNr)
        pl->currentPlayer = 1; // if the current player is the last one, swap to the first one
    else
        pl->currentPlayer++; // else simply increase the currentPlayer counter
}

void canMove(struct Tile board[][MAX_SIZE], struct Player players[], struct Game *ptr)
{
    for (int i = 1; i <= ptr->y; i++)
    {
        for (int j = 1; j <= ptr->x; j++)
        {
            if (board[i][j + 1].fish == 0 && board[i][j - 1].fish == 0 && board[i - 1][j].fish == 0 && board[i + 1][j].fish == 0 && board[i][j].isActive && board[i][j].player != 0)
            {
                board[i][j].isActive = false;               // removes the ice floe from the game
                ptr->freePenguins--;                        // removes the amount of penguins in the game that can be moved
                players[board[i][j].player].freePenguins--; // reduces the amount of free penguins the player has
            }
        }
    }
}