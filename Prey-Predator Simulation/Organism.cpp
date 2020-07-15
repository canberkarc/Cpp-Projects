
/**
 * The Class file for our Organism class.
**/

#include "Organism.h"

/**
 * Empty constructor
 * @brief Organism::Organism
 */
Organism::Organism(){
    survivedStep = 0;
    species = ' ';
    isAlreadyMoved = false;
}

/**
 * Destructor
 * Organism::~Organism
 */
Organism::~Organism()
{}

/**
 * Getter
 * @brief Organism::getMoved
 * @return bool
 */
bool Organism::getMoved() const
{
    return isAlreadyMoved;
}

/**
 * Setter
 * @brief Organism::setMoved
 * @param value
 */
void Organism::setMoved(bool value)
{
    isAlreadyMoved = value;
}

/**
 * given a position of the cell (x,y),  returns
 * @brief Organism::getMovesToEmptyCells
 * @param world : game pad
 * @param pos : position * : current position
 * @return PositionArray * : a list of valid position to adjacent empty cells
 */
PositionArray * Organism::getAdjacentEmptyCells(Organism ***world, Position * pos)
{
    PositionArray * emptyCells = new PositionArray();

    for (int direction = LEFT; direction <= DOWN; direction++){
      Position * posTemp = new Position();
      posTemp =  getPosition(pos, direction);
      if (!isValidPosition(posTemp)) continue;
      if (world[posTemp->getXPos()][posTemp->getYPos()]->getSpecies() == ' ')
        emptyCells->append(*posTemp);
    }
    return emptyCells;
}
/**
 * Check the position to be right. For example, whether is not edge.
 * @brief Organism::isValidPostion
 * @param pos : current position
 * @return  : true if checked is ok.
 */
bool Organism::isValidPosition(Position * pos)
{
    if (pos->getXPos() < 0 || pos->getXPos() >= rows || pos->getYPos() < 0 || pos->getYPos() >= columns)
      return false;
    return true;
}
/**
 * Get a valid direction from grid[x][y], updates x and y according to the direction
 * @brief Organism::getPosition
 * @param pos : current position
 * @param direction : direction to get new position.
 */
Position * Organism::getPosition(Position * pos, int direction)
{
    Position * posTemp = new Position();
    int tempx = pos->getXPos();
    int tempy = pos->getYPos();
    if (direction == LEFT) tempx--;
    if (direction == RIGHT) tempx++;
    if (direction == DOWN) tempy--;
    if (direction == UP) tempy++;
    posTemp->setXPos(tempx);
    posTemp->setYPos(tempy);
    return posTemp;
}

/**
 * Generate a random number
 * @brief Organism::generateRandomNumber
 * @param start : start number of rand
 * @param end : end number of rand
 * @return int
 */
int Organism::generateRandomNumber(int start, int end)
{
    int rnd = rand() % (end - start + 1);
    return rnd;
}
/**
 * Generate a random number from 1 to 4
 * @brief Organism::generateRandomNumber
 * @return int
 */
int Organism::generateRandomDirection()
{
    return rand() % 4;
}

/**
 * Replace the critter with empty
 * @brief Organism::replaceWithEmpty
 * @param world : game pad
 * @param pos : position to be replaced
 */
void Organism::replaceWithEmpty(Organism ***world, Position *pos)
{
    //Delete the critter on the old position.
    delete world[pos->getXPos()][pos->getYPos()];
    //Create the new critter.
    world[pos->getXPos()][pos->getYPos()] = new Organism();
}

/**
 * Getter for the species of current critter
 * Organism::getSpecies
 * @return species
 */
char Organism::getSpecies()
{
    return species;
}

/**
 * Funcion for moving of Critter
 * Organism::move
 * @param world : game pad
 */
void Organism::move(Organism*** world)
{
    species = ' ';
}

/**
 * Breed for critter
 * Organism::breed
 * @param world : game pad
 * @param row : current x position
 * @param col : current y position
 */
bool Organism::breed(Organism*** world)
{
    species = ' ';
    return true;
}

/**
 * Only use for doodlebugs
 * Organism::starve
 * @param world : game pad
 */
void Organism::starve(Organism *** world)
{

}

/**
 * The function for killing doodlebug after poison Ant
 * @param world : game pad
 */
void Organism::poisonous(Organism ***world)
{

}
