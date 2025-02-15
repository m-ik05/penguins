#include "lib.h"

// structure describing player profile
struct Player
{
    int id;           // player's id
    int penguinNr;    // number of penguins the player has
    int freePenguins; // number of available penguins (to be placed or moved, depending on the phase)
    int score;        // player's score (amount of fish they have)
    char name[20];    // player's name
};
// function creates a player profile that contains player score
// arguments = player's id and number of penguins they have
struct Player createPlayer(int, int);