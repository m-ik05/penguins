#include "../headers/movement.h"

void movementPhase(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[], FILE *fp, char filename[])
{
    struct Tile selected;

    system("cls");
    printf("MOVEMENT PHASE\n");
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

    selected = selectPenguin(ptr, board, players);
    movePenguin(ptr, board, selected, players);
    updateFile(*ptr, board, players, fp, filename);
}

struct Tile selectPenguin(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[])
{
    int x, y;
    struct Tile temp;
    // until the player enters valid coordinates
    do
    {
        printf("Player %d turn\n", ptr->currentPlayer);
        printf("Penguins's left: %d\n", players[ptr->currentPlayer].freePenguins);
        printf("Penguins left in the game: %d\n", ptr->freePenguins);
        printf("Player's left in the game: ");
        for (int i = 1; i <= ptr->playerNr; i++)
            if (players[i].freePenguins != 0)
                printf("%d ", i);
        printf("\n");
        showBoard(*ptr, board, players);

        printf("Select which penguin you want to move\n");
        printf("x: ");
        scanf("%d", &x);
        printf("y: ");
        scanf("%d", &y);

        system("cls");
    } while (!checkSelected(x, y, ptr->x, ptr->y, board[y][x], ptr->currentPlayer));
    temp.x = x;
    temp.y = y;
    return temp;
}

int checkSelected(int x, int y, int board_x, int board_y, struct Tile selected, int currentPlayer)
{
    bool validCoordinates = (x >= 0 && x <= board_x && y >= 0 && y <= board_y);
    // checks if inserted coordinates are within our game borders
    if (!validCoordinates)
    {
        printf("Invalid coordinates!\n");
        return 0;
    }
    // checks if selected penguin can move
    else if (!selected.isActive)
    {
        printf("Selected penguin cannot move!\n");
        return 0;
    }
    // checks if there are penguins on the floe
    else if (selected.isFree)
    {
        printf("There are no penguins on the ice floe\n");
        return 0;
    }
    // checks if the penguin belongs to the player
    else if (!(selected.player == currentPlayer))
    {
        printf("This penguin does not belong to you!\n");
        return 0;
    }
    else
        return 1;
}

void movePenguin(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Tile temp, struct Player players[])
{
    int x, y;
    int pl = ptr->currentPlayer;
    // until the player enters valid coordinates
    do
    {
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

        printf("Select where do you want to move the penguin\n");
        printf("x: ");
        scanf("%d", &x);
        printf("y: ");
        scanf("%d", &y);

        system("cls");
    } while (!checkMove(x, y, ptr->x, ptr->y, board[y][x], pl, temp.x, temp.y, board));

    board[y][x].player = pl;                  // updates what player is occupying the floe
    board[y][x].isFree = false;               // updates that the floe is occupied
    takeFish(&players[pl], board[y][x].fish); // updates current player's score
    board[y][x].fish = 0;                     // removes all fish from the floe
    board[temp.y][temp.x].player = 0;         // updates that the floe has no players on it
    board[temp.y][temp.x].isFree = true;      // updates that the ice floe is free

    canMove(board, players, ptr); // checks if the player can move the penguin after it moved
}

int checkMove(int x, int y, int board_x, int board_y, struct Tile selected, int currentPlayer, int selected_x, int selected_y, struct Tile board[][MAX_SIZE])
{
    bool validCoordinates = (x >= 1 && x <= board_x && y >= 1 && y <= board_y);
    bool isStraight = (x == selected_x || y == selected_y);
    bool isSelected = (x == selected_x && y == selected_y);

    // checks if the inserted coordinates are within the board borders
    if (!validCoordinates)
    {
        printf("Invalid coordinates!\n");
        return 0;
    }
    // checks if the coordinates inserted move the penguin
    else if (isSelected)
    {
        printf("You need to move the penguin!\n");
        return 0;
    }
    // checks if the penguin will move in a straight line
    else if (!isStraight)
    {
        printf("Penguin needs to move in a straight line!\n");
        return 0;
    }
    // checks if the penguin will above empty ice floes
    else if (!wayFree(x, y, selected_x, selected_y, board))
    {
        printf("Penguin cannot move above other penguins or empty ice floes!\n");
        return 0;
    }
    // checks if the ice floe is occupied
    else if (!selected.isFree)
    {
        printf("Selected ice floe is occupied already!\n");
        return 0;
    }
    // checks if the ice floe has fish on it
    else if (selected.fish == 0)
    {
        printf("The ice floe is empty!\n");
        return 0;
    }
    else
        return 1;
}

int wayFree(int x, int y, int start_x, int start_y, struct Tile board[][MAX_SIZE])
{
    if (start_x == x) // if the player moves in the y dimension (up or down)
    {
        if (start_y < y) // if the player moves down
        {
            for (int i = start_y + 1; i < y; i++)
                if (board[i][x].fish == 0 || !board[i][x].isFree)
                    return 0;
        }
        else if (start_y > y) // if the player moves up
        {
            for (int i = start_y - 1; i > y; i--)
                if (board[i][x].fish == 0 || !board[i][x].isFree)
                    return 0;
        }
    }
    else if (start_y == y) // if the player moves in the x dimension (left or right)
    {
        if (start_x < x) // if the player moves right
        {
            for (int i = start_x + 1; i < x; i++)
                if (board[y][i].fish == 0 || !board[y][i].isFree)
                    return 0;
        }
        else if (start_x > x) // if the player moves left
        {
            for (int i = start_x - 1; i > x; i--)
                if (board[y][i].fish == 0 || !board[y][i].isFree)
                    return 0;
        }
    }
    return 1;
}