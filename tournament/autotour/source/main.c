#include "../headers/general.h"

// simple function that prints an error message if there are wrong command line parameters provided
void errormsg();

int main(int argc, char *argv[])
{
    // checks if the number of parameters is correct
    if (argc < 4 || argc > 6)
    {
        errormsg();
        return 3;
    }
    // checks that if the phase is not placement, is the number of penguins provided
    if (strcmp(argv[1], "phase=placement"))
    {
        if (argc < 4 || argc > 5 || strcmp(argv[2], argv[3]))
        {
            errormsg();
            return 3;
        }
    }

    // declaration of structures
    struct Game game;
    struct Tile board[MAX_SIZE][MAX_SIZE];
    struct Player players[MAX_PLAYERS + 1];
    FILE *fp;

    // setup(&game, board, players, fp, argv[3]); // uncomment when creating a new file with the board, comment after creating it
    readFile(&game, board, players, fp, argv[3]);

    // the game itself is played in these functions
    if (!strcmp(argv[1], "phase=placement"))
    {
        if (argc == 6)
        {
            printf("%s", argv[5]);
            return 0;
        }
        int pengNr = argv[2][9] - '0';
        contPlace(&game, board, players, pengNr);
        placementPhase(&game, board, players, fp, argv[3]);
        if (game.freePenguins) // if there are still penguins to be placed return 0
            return 0;
        else // else signal that all penguins have been placed
            return 1;
    }
    else if (!strcmp(argv[1], "phase=movement"))
    {
        if (argc == 5)
        {
            printf("%s", argv[4]);
            return 0;
        }
        contMove(&game, board, players);
        movementPhase(&game, board, players, fp, argv[3]);
        if (game.freePenguins)
            return 0;
        else
            return 1;
    }
    else
    {
        errormsg();
        return 3;
    }
    int fclose(FILE * fp);
}

void errormsg()
{
    printf("Error in parameters provided!\n");
    printf("It should be:\n");
    printf("\tphase=placement or phase=movement\n");
    printf("\tpenguins=N (N=number of penguins, only if phase is placement)\n");
    printf("\tinputboardfile (name of the game file)\n");
    printf("\toutputboardfile (name of the game file)\n");
    printf("\tname (request to display player's name and exit the program) (optional)\n");
}