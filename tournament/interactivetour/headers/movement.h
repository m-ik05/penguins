#include "../headers/general.h"

// Selects a penguin belonging to the player
// arguments = pointer to our game conditions, the board and the array of all players
struct Tile selectPenguin(struct Game *, struct Tile[][MAX_SIZE], struct Player[]);

// Checks if chosen penguin has any moves left
// arguments = inputed x and y coordinates, size of the board, selected tile and who is the current player
int checkSelected(int, int, int, int, struct Tile, int);

// Request coordinates where to move selected penguin
// arguments = pointer to game conditions, board, temporary tile (access to the coordinates of the penguin before movement, array of players, array of penguins)
void movePenguin(struct Game *, struct Tile[][MAX_SIZE], struct Tile, struct Player[]);

// Checks if chosen place is available
// arguments = inputed x and y coordinates, board size, selected tile, who is the current player, current penguin coordinates, the board
int checkMove(int, int, int, int, struct Tile, int, int, int, struct Tile[][MAX_SIZE]);

// Checks if there is a way between selected points
//  arguments = final x, final y, initial x, initial y, board
int wayFree(int x, int y, int start_x, int start_y, struct Tile board[][MAX_SIZE]);