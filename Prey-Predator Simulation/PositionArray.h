#ifndef POSITIONARRAY_H
#define POSITIONARRAY_H

#include "Position.h"

class PositionArray
{
public:
    PositionArray();
    ~PositionArray();
    int append(Position pos);
    int size()const;
    bool contains(Position pos);
    Position getAt(int index);
private:
    Position * innerArray;
    int length;
};

#endif // POSITIONARRAY_H
