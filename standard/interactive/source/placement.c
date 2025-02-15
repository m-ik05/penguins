#include "../headers/placement.h"

int checkFloe(int x, int y, int board_x, int board_y)
{
    return (x >= 1 && x <= board_x && y >= 1 && y <= board_y);
}
void placePenguin(int x, int y, struct Tile board[][MAX_SIZE], int plNr, struct Player *pl)
{
    board[y][x].player = plNr;      // updates what player is occupying the floe
    board[y][x].isFree = false;     // updates that the floe is occupied
    takeFish(pl, board[y][x].fish); // updates score
    board[y][x].fish = 0;           // removes all fish from the floe
    pl->freePenguins--;             // reduces the amount of available penguins the player has
}

void placementPhase(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[])
{
    int x, y;
    int canPlace = 0; // counts all penguins in the game. When it reaches 0, that means that all penguins have been placed and we can move on to the movement phase
    for (int i = 0; i < ptr->playerNr; i++)
        for (int j = 0; j < ptr->penguinNr; j++)
            canPlace++;

    system("cls");
    printf("PLACEMENT PHASE\n");
    // as long as there are penguins to place
    do
    {
        // the loop works until the player inputs valid coordinates for placing the penguin
        do
        {
            // prints game information
            printf("Player %d turn\n", ptr->currentPlayer);                            // whose turn is it
            printf("Penguins's left: %d\n", players[ptr->currentPlayer].freePenguins); // how many penguins can they place
            showBoard(*ptr, board, players);

            printf("Select where to put the penguin: \n");
            printf("x: ");
            scanf("%d", &x);
            printf("y: ");
            scanf("%d", &y);

            system("cls");
            // checks if inserted coordinates are within the game borders
            if (!checkFloe(x, y, ptr->x, ptr->y))
                printf("Invalid coordinates!\n");
            // checks if the ice floe is empty
            else if (!board[y][x].isFree)
                printf("Selected ice floe is already occupied!\n");
            // checks if the ice floe has exactly one fish on it
            else if (board[y][x].fish != 1)
                printf("Ice floe needs to have only 1 fish on it!\n");
        } while (!checkFloe(x, y, ptr->x, ptr->y) || !board[y][x].isFree || board[y][x].fish != 1);
        placePenguin(x, y, board, ptr->currentPlayer, &players[ptr->currentPlayer]);
        canMove(board, players, ptr); // checks if the player can move the penguin after being placed

        canPlace--;
        swapPlayer(ptr);
    } while (canPlace);
}