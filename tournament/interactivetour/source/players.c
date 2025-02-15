#include "../headers/lib.h"
#include "../headers/players.h"

struct Player createPlayer(int id, int pe)
{
    struct Player temp = {id, pe, pe, 0, 0};
    return temp;
}