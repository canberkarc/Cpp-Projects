/**
 * The class for storing positions as array type
*/
#include "PositionArray.h"

/**
 * Constructor
 * @brief PositionArray::PositionArray
 */
PositionArray::PositionArray()
{
    innerArray = new Position[0];
    length = 0;
}
/**
 * Destructor
 * @brief PositionArray::~PositionArray
 */
PositionArray::~PositionArray()
{
    //Free heap
    delete [] innerArray;
    length = 0;
}
/**
 * Append new value into array tail
 * @brief PositionArray::append
 * @param pos : appended position
 * @return int : length
 */
int PositionArray::append(Position pos)
{
    Position *tmp = new Position[length + 1];
    for(int i = 0; i < length; i++){
        tmp[i] = innerArray[i];
    }
    tmp[length] = pos;
    innerArray = new Position[length + 1];
    //Increase length.
    length++;
    for(int i = 0; i < length ; i ++){
        innerArray[i] = tmp[i];
    }
    return length;
}
/**
 * Return length
 * @brief PositionArray::size
 * @return length
 */
int PositionArray::size() const
{
    return length;
}

/**
 * Check whether contains pos
 * @brief PositionArray::contains
 * @param pos : input pos
 * @return bool : if contains, return true.
 */
bool PositionArray::contains(Position pos)
{
    for(int i = 0; i < length; i ++){
        Position tmp = innerArray[i];
        if(tmp.isEquals(pos)){
            return true;
        }
    }
    return false;
}
/**
 * Get the value to be placed in index.
 * @brief PositionArray::getAt
 * @param index : from 0.
 * @return Position
 */
Position PositionArray::getAt(int index)
{
    Position * ret;
    if(length > index){
        ret = &innerArray[index];
    }else{
        ret = new Position();
    }
    return *ret;
}
