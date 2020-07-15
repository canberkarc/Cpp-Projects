#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <time.h>
#include <stdlib.h>

#include "GamePad.h"
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"

class Player
{
public:
    Player(int ants, int doodlebugs);
    void start();
private:
    void step();
    GamePad * gamePad;
};

#endif // PLAYER_H
