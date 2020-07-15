#ifndef DOODLEBUG_H
#define DOODLEBUG_H

#include "Organism.h"

class Doodlebug : public Organism
{
private:
    //the step from last eat any ant.
    int starvingStep;
    //the step number from eating poisonous ant.
    int stepFromEatingPoison;
    bool isEatingPoison;
public:

    Doodlebug(Position *pos, int survived, int starve,
              int poisonAnt);

    ~Doodlebug();

    void move(Organism ***world);

    bool breed(Organism ***world);

    void starve(Organism*** world);

    void poisonous(Organism *** world);
private:
    void moveDoodlebug(Organism *** world, Position *pos);

    void replaceWithDoodlebug(Organism *** world, Position *pos, int survived,
                              int starve, int poisonAnt);

    PositionArray *getAdjacentAntCell(Organism *** world);
};

#endif // DOODLEBUG_H
