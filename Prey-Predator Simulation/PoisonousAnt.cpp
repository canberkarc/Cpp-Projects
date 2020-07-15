/**
 * The class body file for PoisonousAnt class
*/
#include "PoisonousAnt.h"

PoisonousAnt::PoisonousAnt()
{

}
/**
 * constructor for poisonous ant objects
 * PoisonousAnt::PoisonousAnt
 * @param pos : position
 * @param alive : the status of ant's alive
 */
PoisonousAnt::PoisonousAnt(Position * pos, int alive)
{
    extern const int ROWS;
    extern const int COLUMNS;
    position = new Position(pos->getXPos(), pos->getYPos());
    species = 'C';
    survivedStep = alive;
    this->rows = ROWS;
    this->columns = COLUMNS;
}

/**
 * Destructor
 * PoisonousAnt::~PoisonousAnt
 */
PoisonousAnt::~PoisonousAnt()
{}

/**
 * The function for the moving of poisonous ant
 * PoisonousAnt::move
 * @param world : game board
 */
void PoisonousAnt::move(Organism ***world)
{
    //If already moved, return.
    if(isAlreadyMoved){
        return;
    }
    //Get the direction to move.
    int direction = generateRandomDirection();
    //Get position for moving
    Position * pos = getPosition(position, direction);
    //Check the validation of new position to move.
    if(isValidPosition(pos)){
        moveAnt(world, pos);
    }
    isAlreadyMoved = true;
}

/**
 * Replace the critter on the old position with new ant so that simulate the moving of ant.
 *  Ant::moveAnt
 * @param world : game pad.
 * @param pos : new position to be moved
 */
void PoisonousAnt::moveAnt(Organism ***world, Position * pos)
{
    int newX = pos->getXPos();
    int newY = pos->getYPos();
    if(world[newX][newY]->getSpecies() ==' ')
    {
        //Delete the critter on the new position to create new ant
        delete world[newX][newY];
        //Create the new ant
        world[newX][newY] = new PoisonousAnt(pos, ++survivedStep);
        //Set moved variable as true so that protect the moving again.
        world[newX][newY]->setMoved(true);
        //replace with empty
        replaceWithEmpty(world, position);
    }
    else
    {
        survivedStep++;
    }
}

/**
 * The function for the breed of PoisonousAnt
 * Ant::breed
 * @param world : game board
 * @param rows : current x position
 * @param columns : current y position
 * @return bool : if success to breed, true. this is only used for mutation.
 */
bool PoisonousAnt::breed(Organism ***world)
{
    //Check whether this ant survives for three steps
    if(survivedStep == 4){
        //Get valid cells to breed
        PositionArray *validCells = getPositionToMove(world);
        int size = validCells->size();
        //If no valid cell
        if(size == 0){
            return true;
        }
        //Get postion to breed that try lastly or empty.
        Position pos = validCells->getAt(size - 1);
        //Delete the new position's critter and create new ant.
        delete world[pos.getXPos()][pos.getYPos()];
        world[pos.getXPos()][pos.getYPos()] = new PoisonousAnt(&pos, 0);
        //Set alived step as 0
        survivedStep = 0;
    }
    return false;
}

/**
 * Get position array to be moved.
 * @brief PoisonousAnt::getPositionToMove
 * @param world
 * @return position array to be possible.
 */
PositionArray *PoisonousAnt::getPositionToMove(Organism ***world)
{
    int invalidPosition = 0;
    PositionArray * ret = new PositionArray();
    while (ret->size() < 4) {
        int direction = generateRandomDirection();
        Position * pos = getPosition(position, direction);
        if(isValidPosition(pos)){
            //If contains pos.
            if(ret->contains(*pos)){
                continue;
            }
            ret->append(*pos);
            //If the tried position is empty, finish the loop and return.
            if(world[pos->getXPos()][pos->getYPos()]->getSpecies() == ' '){
                break;
            }
        }else{
            invalidPosition++;
        }
        //If the sum of ret's size and invalid position' number, escape loop.
        if((ret->size() + invalidPosition) == 4){
            break;
        }
    }
    return ret;
}
