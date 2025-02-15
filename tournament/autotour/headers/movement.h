#include "../headers/general.h"

// Request coordinates where to move selected penguin
// arguments = pointer to game conditions, board, temporary tile (access to the coordinates of the penguin before movement, array of players, array of penguins)
void movePenguin(struct Game *, struct Tile[][MAX_SIZE], struct Tile, struct Player[]);

// The program makes the move, by selecting a path that has the most amount of moves in a straight line
// arguments = initial x, initial y, board
struct Tile makeMove(int, int, struct Tile[][MAX_SIZE]);