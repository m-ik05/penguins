#include "../headers/general.h"

// Checks if selected ice floe is free
// arguments = selected x and y coordinates and game board size
int checkFloe(int, int, int, int);

// Places penguin on the selected ice floe
// arguments = x and y coordinates, the board and current player's number, pointer to the current player's structure
void placePenguin(int, int, struct Tile[][MAX_SIZE], int, struct Player *);