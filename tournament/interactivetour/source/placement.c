#include "../headers/placement.h"

void placementPhase(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[], FILE *fp, char filename[])
{
    int x, y;

    system("cls");
    printf("PLACEMENT PHASE\n");
    do
    {
        // prints game information
        printf("Player %d turn\n", ptr->currentPlayer);
        printf("Penguins's left: %d\n", players[ptr->currentPlayer].freePenguins);
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
    if (!board[y][x].isActive)
        ptr->freePenguins++; // in case the penguin is blocked, we increase the amount of free penguins (to counteract the fact that it was reduced in canMove function). It comes due to the fact that in placement phase placing the penguin already reduces the number, while in movement only after it's blocked
    updateFile(*ptr, board, players, fp, filename);
}

void placePenguin(int x, int y, struct Tile board[][MAX_SIZE], int plNr, struct Player *pl)
{
    board[y][x].player = plNr;      // updates what player is occupying the floe
    board[y][x].isFree = false;     // updates that the floe is occupied
    takeFish(pl, board[y][x].fish); // updates score
    board[y][x].fish = 0;           // removes all fish from the floe
    pl->freePenguins--;             // reduces the amount of available penguins the player has
}

int checkFloe(int x, int y, int board_x, int board_y)
{
    return (x >= 1 && x <= board_x && y >= 1 && y <= board_y);
}