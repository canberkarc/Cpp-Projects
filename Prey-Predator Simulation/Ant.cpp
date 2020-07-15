
/**
 * The class body file for our Ant child class.
**/

#include "Ant.h"

/**
 * Default constructor
 * @brief Ant::Ant
 */
Ant::Ant(){

}

/**
 * constructor for ant objects
 * Ant::Ant
 * @param pos : current position
 * @param alive : the status of ant's alive
 */
Ant::Ant(Position * pos, int alive)
{    
    extern const int ROWS;
    extern const int COLUMNS;
    position = new Position(pos->getXPos(), pos->getYPos());
    species = 'O';
    survivedStep = alive;
    this->rows = ROWS;
    this->columns = COLUMNS;
}

/**
 * Destructor
 * Ant::~Ant
 */
Ant::~Ant()
{}

/**
 * The function for the moving of ant
 * Ant::move
 * @param world : game board
 */
void Ant::move(Organism ***world)
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
 * @param pos: new postion
 */
void Ant::moveAnt(Organism ***world, Position *pos)
{
    int newX = pos->getXPos();
    int newY = pos->getYPos();
    if(world[newX][newY]->getSpecies() ==' ')
    {
        //Delete the critter on the new position to create new ant
        delete world[newX][newY];
        //Create the new ant
        world[newX][newY] = new Ant(pos, ++survivedStep);
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
 * The function for the breed of ant
 * Ant::breed
 * @param world : game board
 * @param rows : current x position
 * @param columns : current y position
 */
bool Ant::breed(Organism ***world)
{
    //Check whether this ant survives for three steps
    if(survivedStep >= 3){
        //Get empty cells to breed by using direction enum values
        PositionArray * emptyCells = getAdjacentEmptyCells(world, position);
        int size = emptyCells->size();
        //If no empty cell, return false for mutation
        if(size == 0){
            survivedStep = 0;
            return true;
        }
        //Get position to breed according to the direction.
        Position pos = emptyCells->getAt(generateRandomNumber(0, size - 1));
        //Delete the new position's critter and create new ant.
        delete world[pos.getXPos()][pos.getYPos()];
        world[pos.getXPos()][pos.getYPos()] = new Ant(&pos, 0);
        //Set alived step as 0
        survivedStep = 0;
    }
    return false;
}
