#include "lib.h"
// structure responsible for gamestate
struct Game
{
    int x;             // x board dimensions
    int y;             // y board dimensions
    int playerNr;      // number of players
    int penguinNr;     // number of penguins available to each player
    int currentPlayer; // whose turn is it
    int freePenguins;  // how many free penguins are in the game
};
// structure responsible for one tile on the board
struct Tile
{
    int y;         // y coordinates
    int x;         // x coordinates
    int fish;      // number of fish on the tile
    int player;    // what player is occupying the tile
    bool isFree;   // check if there is a penguin on the tile
    bool isActive; // check if the tile is still in the game (can the penguin standing on it move anywhere)
};

// Using dimensions provided in the setup() function createBoard is going to create the board
// arguments = x dimensions, y dimensions, and an array of tiles (our board)
void createBoard(int, int, struct Tile[][MAX_SIZE]);

// The function will create a new tile for our board, which is essentially an array of Tile structures
// arguments = x coordinates, y coordiantes, number of fish that are on the tile
struct Tile createTile(int, int, int);