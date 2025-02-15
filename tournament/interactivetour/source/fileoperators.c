#include "../headers/general.h"

void readFile(struct Game *ptr, struct Tile board[][MAX_SIZE], struct Player players[], FILE *fp, char filename[])
{
    char tempc;   // temporary character for getc
    char cx[2];   // array for x dimensions
    char cy[2];   // array for y dimensions
    int x;        // x dimensions
    int y;        // y dimensions
    int ID = 1;   // player's id
    int plNr = 0; // number of players
    int fish, player;
    char buffer[20]; // an array of chars to read strings for name
    char score[3];   // an array of chars to read the score

    fp = fopen(filename, "r"); // opens the file for reading

    // gets y dimensions
    cy[0] = fgetc(fp); // first digit of y dimensions
    tempc = fgetc(fp); // either whitespace or second digit of y dimensions
    if (tempc != ' ')  // if provided y dimensions are more than 9
    {
        cy[1] = tempc;     // second digit of y dimensions
        y = atoi(cy);      // converts the character array into y dimensions
        tempc = fgetc(fp); // whitespace
    }
    else // if provided dimensions are less or equal to 9
        y = cy[0] - '0';

    // gets x dimensions
    cx[0] = fgetc(fp); // first digit of x dimensions
    tempc = fgetc(fp); // either end of line or second digit of x dimensions
    if (tempc != '\n') // if provided x dimensions are more than 9
    {
        cx[1] = tempc;     // second digit of x dimensions
        x = atoi(cx);      // converts the character array of x dimensions
        tempc = fgetc(fp); // end of line
    }
    else // if provided dimensions are less or equal to 9
        x = cx[0] - '0';

    int i = 1;
    while (!feof(fp))
    {
        // read the board itself
        if (i > 0 && i <= y)
        {
            for (int j = 1; j <= x; j++)
            {
                tempc = fgetc(fp); // gets the number of fish
                fish = tempc - '0';
                board[i][j] = createTile(i, j, fish);

                tempc = fgetc(fp); // gets what player is on the floe
                board[i][j].player = tempc - '0';
                if (tempc - '0')
                    board[i][j].isFree = false;

                tempc = fgetc(fp); // whitespace
            }
            tempc = fgetc(fp); // moves to the next line
        }
        // read player info
        if (i > y)
        {
            int t = 0;
            tempc = fgetc(fp); // first character of player's name
            while (tempc != ' ')
            {
                buffer[t] = tempc;
                t++;
                tempc = fgetc(fp); // another character / whitespace
            }
            strcpy(players[ID].name, buffer); // copying player's name from the buffer

            tempc = fgetc(fp); // getting player's id
            players[ID].id = tempc - '0';
            tempc = fgetc(fp); // whitespace

            t = 0;
            tempc = fgetc(fp); // getting player's score
            while (tempc != '\n' || feof(fp))
            {
                score[t] = tempc;
                t++;
                tempc = fgetc(fp);             // another digit or end of line
                if (tempc == '\n' || feof(fp)) // backup in case the condition in while doesn't work
                    break;
            }
            players[ID].score = atoi(score); // converts the character array into score
            ID++;
            plNr++;
        }
        i++;
    }
    ptr->x = x;
    ptr->y = y;
    ptr->playerNr = plNr;
    fclose(fp); // close the file
}

void updateFile(struct Game game, struct Tile board[][MAX_SIZE], struct Player players[], FILE *fp, char filename[])
{
    int x = game.x;            // x dimensions
    int y = game.y;            // y dimensions
    int plNr = game.playerNr;  // number of players
    fp = fopen(filename, "w"); // opens the file for writing
    int c = 1;
    for (int i = 0; i < y + plNr + 1; i++)
    {
        // saves board dimensions
        if (i == 0)
            fprintf(fp, "%d %d\n", y, x);
        // saves the board itself
        if (i > 0 && i <= y)
        {
            for (int j = 1; j <= x; j++)
                fprintf(fp, "%d%d ", board[i][j].fish, board[i][j].player);
            fprintf(fp, "\n");
        }
        // saves player info
        if (i > y)
        {
            fprintf(fp, "%s %d %d", players[c].name, players[c].id, players[c].score);
            if (i != y + plNr) // makes sure there is no additional empty line at the end of the file
                fprintf(fp, "\n");
            c++;
        }
    }
    fclose(fp); // closes the file
}