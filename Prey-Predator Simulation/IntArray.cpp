#include "IntArray.h"

IntArray::IntArray()
{
    innerArray = new int[0];
    length = 0;
}

IntArray::~IntArray()
{
    delete[] innerArray;
    length = 0;
}

int IntArray::getAt(int position)const
{
    if(length - 1 >= position){
        return innerArray[position];
    }
    return 0;
}
/**
 * Append the value to the end of this
 * @brief IntArray::append
 * @param value
 */
void IntArray::append(int value)
{
    int * temp = new int[length + 1];
    for(int i = 0; i < length; i ++){
        temp[i] = innerArray[i];
    }
    temp[length] = value;
    innerArray = new int[length + 1];
    for(int i = 0; i < length + 1; i++){
        innerArray[i] = temp[i];
    }
    length++;
}
/**
 * Get size
 * @brief IntArray::size
 * @return  the size of array
 */
int IntArray::size()const
{
    return length;
}

/**
 * Check whether contains the value
 * @brief IntArray::contains
 * @param value
 * @return if contains, true.
 */
bool IntArray::contains(int value)
{
    for(int i = 0; i < length ; i ++){
        if(innerArray[i] == value){
            return true;
        }
    }
    return false;
}
