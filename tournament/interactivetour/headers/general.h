#include "lib.h"
#include "board.h"
#include "players.h"

// function to setup the game
// it's not technically neccessary in auto mode as the program reads the gamestate from the file, but it is here as an easy way of actually creating the file
// arguments = pointer to the game structure from main, an array of tiles (our board), an array of all players and an array of all penguins in the game
void setup(struct Game *, struct Tile[][MAX_SIZE], struct Player[], FILE *, char[]);

// function that will read the game file
// arguments = pointer to game conditions, board, player array, pointer to a file, name of the file
void readFile(struct Game *, struct Tile[][MAX_SIZE], struct Player[], FILE *, char[]);

// function that will update the game file
// arguments = game conditions, board, player array, pointer to a file
void updateFile(struct Game, struct Tile[][MAX_SIZE], struct Player[], FILE *, char[]);

// This function will show our board
// arguments = copy of game conditions, board, player array
void showBoard(struct Game, struct Tile[][MAX_SIZE], struct Player[]);

// This function will take the fish from the tile that the penguin lands on and update player's score
// arguments = pointer to the current player's structure and the number of fish
void takeFish(struct Player *, int);

// This function swaps players' turns
// argument = pointer to game conditions, array of all players
void swapPlayer(struct Game *);

// checks if the penguin still has moves
//  arguments = board, penguin's x coordinates, penguin's y coordinates, array of players
void canMove(struct Tile[][MAX_SIZE], struct Player[], struct Game *);

// continues the game if it's placement phase
// arguments = pointer to our game conditions, board, all players and all penguins in the game, number of penguins each player has
void contPlace(struct Game *, struct Tile[][MAX_SIZE], struct Player[], int);

// The function that is responsible for the whole placement phase of the game
// arguments = pointer to our game conditions, board, all players and all penguins in the game
void placementPhase(struct Game *, struct Tile[][MAX_SIZE], struct Player[], FILE *, char[]);

// continues the game if it's movement phase
// arguments = pointer to our game conditions, board, all players and all penguins in the game
void contMove(struct Game *, struct Tile[][MAX_SIZE], struct Player[]);

// Function responsible for the whole movement phase
// arguments = pointer to game conditions, board, array of players, array of penguins
void movementPhase(struct Game *, struct Tile[][MAX_SIZE], struct Player[], FILE *, char[]);