#include "../headers/general.h"

// Selects the tile on which to place the penguin
// arguments = pointer to the game conditions, board, pointer to a player
void selectPenguin(struct Game *, struct Tile[][MAX_SIZE], struct Player *);

// Places penguin on the selected ice floe
// arguments = x and y coordinates, the board and current player's number, pointer to the current player's structure
void placePenguin(struct Game *, struct Tile[][MAX_SIZE], struct Player *, int, int);