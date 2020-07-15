#ifndef GAMEPAD_H
#define GAMEPAD_H
#include "Organism.h"
#include "Ant.h"
#include "Doodlebug.h"
#include "PoisonousAnt.h"
#include <stdlib.h>
#include <iostream>
using std::cout;

class GamePad
{
public:
    GamePad(int ants, int doodlebugs);
    ~GamePad();

    void showGamePad();
    void simulate();
private: //Private functions
    Position * getRandPosition();
    void initGamePad();
    void simulateAnts();
    void simulateDoodlebugs();
    void simulatePoisonAnt();
    void simulateMove(char species);
    void initMovedDirection();
    void initIsAlreadyMoved();
    void mutateAnt2Poison(Position *pos);
    void sprayCritter(OrganismType type, int num);
private: //Private values
    int rows;
    int columns;
    int ants;
    int doodlebugs;
    Organism *** gamePad;
};

#endif // GAMEPAD_H
