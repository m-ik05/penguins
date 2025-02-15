#include "../headers/general.h"

// the function checks who's turn is it in placement phase
// arguments = pointer to game state, board, player array
void placementPlayer(struct Game *, struct Tile[][MAX_SIZE], struct Player[]);

// the function will fill the edges of the border (invisible to the players) with 0 fishes
// arguments = x dimensions, y dimensions, board
void fillEdges(int, int, struct Tile[][MAX_SIZE]);