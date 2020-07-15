#ifndef ORGANISM_H
#define ORGANISM_H

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "IntArray.h"
#include "Position.h"
#include "PositionArray.h"
using namespace std;

enum{LEFT = 0, RIGHT = 1, DOWN = 2, UP = 3};
enum OrganismType
{
    ant,
    doodlebug
};

class Organism
{
protected:
    int survivedStep;
    Position * position;
    char species;
    int moveDirection;
    int rows;
    int columns;
    //If moved, true. This is only used to protect moving again in one step
    bool isAlreadyMoved;

protected:
    PositionArray *getAdjacentEmptyCells(Organism *** world, Position * pos);
    bool isValidPosition(Position *pos) ;
    Position *getPosition(Position *pos, int direction);
    void replaceWithEmpty(Organism *** world, Position * pos);
public:
    Organism();
    virtual void move(Organism *** world);
    virtual bool breed(Organism *** world);
    virtual void starve(Organism *** world);
    virtual char getSpecies();
    virtual void poisonous(Organism *** world);
    virtual ~Organism();
    bool getMoved() const;
    void setMoved(bool value);
    int generateRandomNumber(int start, int end);
    int generateRandomDirection();
};
#endif // ORGANISM_H
