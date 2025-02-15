#include "../headers/general.h"

void setup(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[], FILE *fp, char filename[])
{
    printf("CREATE THE BOARD:\n");
    int x, y, plNr, pengNr;
    printf("Board dimensions(x,y for size inbetween %dx%d and %dx%d):\n", MIN_SIZE, MIN_SIZE, MAX_SIZE - 2, MAX_SIZE - 2);
    do
    {
        printf("x: ");
        scanf("%d", &x);
        if (x > MAX_SIZE - 2)
            printf("Maximal size for x is %d\n", MAX_SIZE - 2);
        if (x < MIN_SIZE)
            printf("Minimal size for x is %d\n", MIN_SIZE);
    } while (x > MAX_SIZE - 2 || x < MIN_SIZE); // checking if provided x coordinates are within boundaries

    do
    {
        printf("y: ");
        scanf("%d", &y);
        if (y > MAX_SIZE - 2)
            printf("Maximal size for y is %d\n", MAX_SIZE - 2);
        if (y < MIN_SIZE)
            printf("Minimal size for y is %d\n", MIN_SIZE);
    } while (y > MAX_SIZE - 2 || y < MIN_SIZE); // checking if provided y coordinates are within boundaries

    do
    {
        printf("Number of players (maximal number is %d): ", MAX_PLAYERS);
        scanf("%d", &plNr);
        if (plNr > MAX_PLAYERS)
            printf("Maximal number of players is %d\n", MAX_PLAYERS);
        if (plNr < 2)
            printf("Minimal number of players is 2\n");
    } while (plNr > MAX_PLAYERS || plNr < 2); // checking if provided number of players is within boundaries

    do
    {
        printf("Number of penguins (maximal number is %d): ", MAX_PENGUINS);
        scanf("%d", &pengNr);
        if (pengNr > MAX_PENGUINS)
            printf("Max number of penguins is %d\n", MAX_PENGUINS);
        if (pengNr < MIN_PENGUINS)
            printf("Minimal number of penguins is %d\n", MIN_PENGUINS);
    } while (pengNr > MAX_PENGUINS || pengNr < MIN_PENGUINS); // checking if number of penguins available to each player is within boundaries

    // assigning inserted values to our game conditions
    ptr->x = x;
    ptr->y = y;
    ptr->playerNr = plNr;
    ptr->penguinNr = pengNr;
    ptr->currentPlayer = 1;
    ptr->freePenguins = plNr * pengNr;

    createBoard(x, y, board); // creating the board

    for (int i = 1; i <= plNr; i++)
    {
        players[i] = createPlayer(i, pengNr); // creating a player profile
    }
    updateFile(*ptr, board, players, fp, filename);
}