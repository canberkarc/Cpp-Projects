/**
 * The class body file for the Doodlebug.
**/

#include "Doodlebug.h"
#include <iostream>

/**
 * The constructor for the Doodlebug
 * Doodlebug::Doodlebug
 * @param pos : Position
 * @param alive : the status for the alive
 * @param starve : the step from the last eating any ant
 * @param poisonAnt : the step from eating poisonous ant
 */
Doodlebug::Doodlebug(Position *pos, int survived, int starve, int poisonAnt)
{
    extern const int ROWS;
    extern const int COLUMNS;
    position = new Position(pos->getXPos(), pos->getYPos());
    species = 'X';
    survivedStep = survived;
    starvingStep = starve;
    stepFromEatingPoison = poisonAnt;
    this->rows = ROWS;
    this->columns = COLUMNS;
}

/**
 * The destructor
 * Doodlebug::~Doodlebug
 */
Doodlebug::~Doodlebug()
{}

/**
 * The function for the moving whenever the enter key is clicked
 * Doodlebug::move
 * @param world : game pad
 */
void Doodlebug::move(Organism ***world)
{
    Position * pos =  new Position();
    //If already moved, return.
    if(isAlreadyMoved){
        return;
    }
    //Get position for ant.
    PositionArray * antPositions = getAdjacentAntCell(world);
    int size = antPositions->size();
    //If there is no any ant on adjancent cells.
    if(size == 0){
        //Get the direction to move.
        int direction = generateRandomDirection();
        //Get position for moving
        pos = getPosition(position, direction);
        //Check the validation of new position to move.
        if(isValidPosition(pos)){
            moveDoodlebug(world, pos);
        }else{
            starvingStep++;
            if(isEatingPoison){
                stepFromEatingPoison++;
            }
        }
    }else{//If there is any ant on adjancent cells.
        *pos = antPositions->getAt(generateRandomNumber(0, size - 1));
        moveDoodlebug(world, pos);
    }
    isAlreadyMoved = true;
}

/**
 * Move a doodlbug to the valid position.
 * If there is ant or poisonous ant, the doodlebug will eat that.
 * @brief Doodlebug::moveDoodlebug
 * @param world : game pad
 * @param pos : position
 */
void Doodlebug::moveDoodlebug(Organism ***world, Position * pos)
{
    Organism * www = world[pos->getXPos()][pos->getYPos()];
    if(www->getSpecies() == ' ')
    {
        //replace critter with doodlebug
        replaceWithDoodlebug(world, pos, ++survivedStep, ++starvingStep,0);
    }else if (www->getSpecies() == 'O') {
        //replace critter with doodlebug
        replaceWithDoodlebug(world, pos, ++survivedStep, 0,0);
    }else if (www->getSpecies() == 'C') {
        if(isEatingPoison){
            //replace critter with doodlebug
            replaceWithDoodlebug(world, pos, ++survivedStep, 0,
                                 ++stepFromEatingPoison);
        }else{
            //replace critter with doodlebug
            replaceWithDoodlebug(world, pos, ++survivedStep, 0,
                                 0);
            isEatingPoison = true;
        }
    }
    else
    {
        survivedStep++;
        starvingStep++;
        if(isEatingPoison){
            stepFromEatingPoison++;
        }
    }
}

/**
 * Replace critter with doodlebug for moving
 * @brief Doodlebug::replaceWithDoodlebug
 * @param world : game pad
 * @param pos : new position
 * @param survived : survived step
 * @param starve : starving step
 * @param poisonAnt : step after eat poisonous ant
 */
void Doodlebug::replaceWithDoodlebug(Organism ***world, Position * pos,
                                     int survived, int starve, int poisonAnt)
{
    int newX = pos->getXPos();
    int newY = pos->getYPos();
    //Delete the critter on the new position to create new ant
    delete world[newX][newY];
    //Create the new ant
    world[newX][newY] = new Doodlebug(pos, survived,
                                      starve, poisonAnt);
    //Set moved variable as true so that protect the moving again.
    world[newX][newY]->setMoved(true);
    //replace with empty
    replaceWithEmpty(world, position);
}

/**
 * Get cells to be filled with ant.
 * @brief Doodlebug::getAdjacentAntCell
 * @param world : game pad
 * @return PositionArray : the cells to be ant.
 */
PositionArray *Doodlebug::getAdjacentAntCell(Organism ***world)
{
    PositionArray * ret = new PositionArray();
    for(int direction = LEFT; direction <= UP ; direction ++){
        Position * pos = new Position();
        pos = getPosition(position, direction);
        if(isValidPosition(pos)){
            if(world[pos->getXPos()][pos->getYPos()]->getSpecies() == 'O' || world[pos->getXPos()][pos->getYPos()]->getSpecies() == 'C'){
                ret->append(*pos);
            }
        }
    }
    return ret;
}

/**
 * The function for breeding
 * Doodlebug::breed
 * @param world : game pad
 */
bool Doodlebug::breed(Organism *** world)
{
    //Check whether this doodlebug survives for 8 steps
    if(survivedStep >= 8){
        //Get empty cells to breed by using direction enum values
        PositionArray * emptyCells = getAdjacentEmptyCells(world, position);
        int size = emptyCells->size();
        //If no empty cell, return
        if(size == 0){
            survivedStep = 0;
            return true;
        }
        //Get breed direction
        int index = generateRandomNumber(0, size - 1);
        //Get postion to breed according to the direction.
        Position pos = emptyCells->getAt(index);
        //Delete the new position's critter and create new doodlebug.
        delete world[pos.getXPos()][pos.getYPos()];
        world[pos.getXPos()][pos.getYPos()] = new Doodlebug(&pos, 0, 0, 0);
        //Set alived step as 0
        survivedStep = 0;
    }
    return false;
}

/**
 * The function for starve status.
 * This checks if doodlebug has not eaten in 3 steps
 * Doodlebug::starve
 * @param world : game pad
 */
void Doodlebug::starve(Organism *** world)
{
    if (starvingStep == 3)
    {
        replaceWithEmpty(world, position);
    }
}
/**
 * The function for killing within 2 steps after eating poisonous ant
 * @brief Doodlebug::poisonous
 * @param world : game pad
 */
void Doodlebug::poisonous(Organism ***world)
{
    if(stepFromEatingPoison == 2){
        replaceWithEmpty(world, position);
    }
}
