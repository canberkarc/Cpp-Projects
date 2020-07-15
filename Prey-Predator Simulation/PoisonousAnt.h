#ifndef POISONOUSANT_H
#define POISONOUSANT_H

#include "Ant.h"

class PoisonousAnt : public Ant
{
public:
    PoisonousAnt();
    PoisonousAnt(Position *pos, int alive);
    ~PoisonousAnt();
    void move(Organism ***world);
    bool breed(Organism ***world);
protected:
    void moveAnt(Organism ***world, Position *pos);
private:
    PositionArray * getPositionToMove(Organism ***world);
};

#endif // POISONOUSANT_H
