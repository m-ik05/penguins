#include "../headers/general.h"

int main()
{
    // declaring our structures
    struct Game game;
    struct Tile board[MAX_SIZE][MAX_SIZE];
    struct Player players[MAX_PLAYERS + 1];

    // running the game
    setup(&game, board, players);
    placementPhase(&game, board, players);
    movementPhase(&game, board, players);

    // checking out who won
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
}