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
        int pengNr = argv[2][9] - '0';
        contPlace(&game, board, players, pengNr);
        placementPhase(&game, board, players, fp, argv[3]);
        movementPhase(&game, board, players, fp, argv[3]);
    }
    else if (!strcmp(argv[1], "phase=movement"))
    {
        contMove(&game, board, players);
        movementPhase(&game, board, players, fp, argv[3]);
    }
    else
    {
        errormsg();
        return 3;
    }

    // picking out the winner
    int max = 0, winner = 0;
    system("cls");
    showBoard(game, board, players);
    printf("GAME OVER!\n");
    for (int i = 1; i <= game.playerNr; i++)
    {
        if (players[i].score > max)
        {
            max = players[i].score;
            winner = i;
        }
        else if (players[i].score == max)
        {
            winner = 0;
        }
    }
    if (winner)
        printf("Winner of the game: %d\n", winner);
    else
        printf("Since two or more players have the same score, there is no singular winner\n");

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