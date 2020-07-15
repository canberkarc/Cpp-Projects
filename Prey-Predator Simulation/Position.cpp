#include "Position.h"

Position::Position()
{
    xPos = 0;
    yPos = 0;
}
/**
 * Constructor with param
 * @brief Position::Position
 * @param x
 * @param y
 */
Position::Position(int x, int y)
{
    xPos = x;
    yPos = y;
}

/**
 * Check whether equals with this and pos
 * @brief Position::isEquals
 * @param pos : position to be checked
 * @return bool : if equals, true.
 */
bool Position::isEquals(Position pos)
{
    if(this->xPos == pos.getXPos() && this->yPos == pos.getYPos()){
        return true;
    }
    return false;
}

int Position::getXPos() const
{
    return xPos;
}

void Position::setXPos(int value)
{
    xPos = value;
}

int Position::getYPos() const
{
    return yPos;
}

void Position::setYPos(int value)
{
    yPos = value;
}
