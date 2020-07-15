#ifndef ANT_H
#define ANT_H

#include "Organism.h"

class Ant : public Organism
{
public:
    Ant();
    Ant(Position *pos, int alive);

    ~Ant();

    virtual void move(Organism ***world);

    virtual bool breed(Organism ***world);

protected:
    virtual void moveAnt(Organism *** world, Position * pos);
};

#endif // ANT_H
