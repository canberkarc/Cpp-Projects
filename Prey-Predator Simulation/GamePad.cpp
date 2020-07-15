#include "GamePad.h"
/**
 * Default constructor
 * GamePad::GamePad
 */
GamePad::GamePad(int ants, int doodlebugs)
{
    extern const int ROWS;
    extern const int COLUMNS;
    this->rows = ROWS;
    this->columns = COLUMNS;
    this->ants = ants;
    this->doodlebugs = doodlebugs;
    //Create GamePad object.
    gamePad = new Organism**[rows];
    //Init the GamePad object.
    initGamePad();
}

/**
 * GamePad::initGamePad
 * After to create game pad object, init that with params.
 */
void GamePad::initGamePad()
{
    for (int rowNum = 0; rowNum < rows; rowNum++)
    {
        gamePad[rowNum] = new Organism*[columns];
    }

    //Init gamePad with Organism objects
    for (int rowNum = 0; rowNum < rows; rowNum++)
    {
        for (int colNum = 0; colNum < columns; colNum++)
        {
            gamePad[rowNum][colNum] = new Organism();
        }
    }

    //Print ants on game pad
    sprayCritter(ant, ants);
    //Print doodlebugs on game pad
    sprayCritter(doodlebug, doodlebugs);
}

/**
 * Spray critters
 * @brief GamePad::sprayCritter
 * @param type : the type of critter
 * @param num : the number of critter
 */
void GamePad::sprayCritter(OrganismType type, int num)
{
    int critterNum = 0;
    while(critterNum < num){
        Position * pos = getRandPosition();
        int x = pos->getXPos();
        int y = pos->getYPos();
        if(gamePad[x][y]->getSpecies() == ' '){
            delete gamePad[x][y];
            if(type == ant){
                gamePad[x][y] = new Ant(pos, 0);
                critterNum++;
            }else if(type == doodlebug){
                gamePad[x][y] = new Doodlebug(pos, 0, 0, 0);
                critterNum++;
            }
        }        
    }
}

/**
 * Generate random position and return it.
 * @brief GamePad::getRandPosition
 * @return position.
 */
Position * GamePad::getRandPosition()
{
    int x = rand() % rows;
    int y = rand() % columns;
    Position * pos = new Position(x, y);
    return pos;
}
/**
 * Destructor
 * In this, free all the heap.
 * GamePad::~GamePad
 */
GamePad::~GamePad()
{
    for (int del = 0; del < rows; del++)
    {
        for (int pt = 0; pt < columns; pt++)
        {
            delete gamePad[del][pt];
        }
        delete[] gamePad[del];
    }
    delete [] gamePad;
    gamePad = NULL;
}

/**
 * GamePad::showGamePad
 * Show the game pad edge and the correct character for each critters on the game pad.
 */
void GamePad::showGamePad()
{
    int antNum = 0;
    int doodleNum = 0;
    int poisonAntNum = 0;

    //The position array to store and track for ant position
    PositionArray * ant_tracks = new PositionArray();
    //The position array to store and track for doodlebug position
    PositionArray * doodlebug_tracks = new PositionArray();
    //The position array to store and track for poisonous ant position
    PositionArray * poison_ant_tracks = new PositionArray();
    //The int array to store and track for ant number.
    IntArray * ant_numbers = new IntArray();
    //The int array to store and track for doodlebug number.
    IntArray * doodlebug_numbers = new IntArray();
    //The int array to store and track for poisonous ant number.
    IntArray * poison_ant_numbers = new IntArray();
    //Paint the edge of game pad with "-" and " | " and the characters for the critters.
    for (int r = 0; r < rows+2; r++)
    {
        for (int c = 0; c < columns+2; c++)
        {
            if (r == 0 || r == rows+1)
            {
                cout << '-';
            }
            else if (c == 0 || c == columns+1)
            {
                cout << '|';
            }
            else
            {
                if(gamePad[r-1][c-1]->getSpecies() == 'O'){
                    Position * pos = new Position(r - 1, c - 1);
                    //Store to track
                    ant_tracks->append(*pos);
                    antNum++;
                }else if(gamePad[r-1][c-1]->getSpecies() == 'X'){
                    Position * pos = new Position(r - 1, c - 1);
                    //Store to track
                    doodlebug_tracks->append(*pos);
                    doodleNum++;
                }else if (gamePad[r-1][c-1]->getSpecies() == 'C') {
                    Position * pos = new Position(r - 1, c - 1);
                    //Store to track
                    poison_ant_tracks->append(*pos);
                    poisonAntNum++;
                }
                cout << gamePad[r-1][c-1]->getSpecies();
            }
        }
        cout << "\n";
    }
    //Store to track
    ant_numbers->append(antNum);
    doodlebug_numbers->append(doodleNum);
    poison_ant_numbers->append(poisonAntNum);
    cout << "\n" << "Ants: " << antNum << " Doodlebugs: " << doodleNum
         << " : Poisonous Ants: " << poisonAntNum <<endl;
}

/**
 * GamePad::simulate
 * Simulate the game with corresponding rules.
 */
void GamePad::simulate()
{
    //simulation for doodlebugs
    //Doodlebugs move before the ants
    simulateDoodlebugs();

    //simulation for ants
    //Ants move before poisonous ants
    simulateAnts();

    //simulation for poisonous ant
    simulatePoisonAnt();
    
    //init the isMoved variable for the next move.
    initIsAlreadyMoved();
}

/**
 * Simulate the behavior of ants
 * @brief GamePad::simulateAnts
 */
void GamePad::simulateAnts()
{
    //Move ants
    simulateMove('O');
    //Breed or mutate
    for (int rowNum = 0; rowNum < rows; rowNum++)
    {
        for (int colNum = 0; colNum < columns; colNum++)
        {
            if(gamePad[rowNum][colNum]->getSpecies() == 'O')
            {
                bool isMutating = gamePad[rowNum][colNum]->breed(gamePad);
                //If can not breed and rnd is 77, then will be mutated.
                int rnd = gamePad[rowNum][colNum]->generateRandomNumber(1, 100);
                if(isMutating && rnd == 77){
                    Position * pos = new Position(rowNum, colNum);
                    mutateAnt2Poison(pos);
                }
            }
        }
    }
}

/**
 * Simulate the behavior of doodlebugs
 * @brief GamePad::simulateDoodlebugs
 */
void GamePad::simulateDoodlebugs()
{
    //Move doodlebugs
    simulateMove('X');
    for (int rowNum = 0; rowNum < rows; rowNum++)
    {
        for (int colNum = 0; colNum < columns; colNum++)
        {
            if(gamePad[rowNum][colNum]->getSpecies() == 'X')
            {
                //Breed
                gamePad[rowNum][colNum]->breed(gamePad);
                //Check whether starve and kill if so.
                gamePad[rowNum][colNum]->starve(gamePad);
                //Check whether eat poisonous ant
                gamePad[rowNum][colNum]->poisonous(gamePad);
            }
        }
    }
}

/**
 * Simulate the behavior of poisonous ants
 * @brief GamePad::simulatePoisonAnt
 */
void GamePad::simulatePoisonAnt()
{
    //Move poisonous ants
    simulateMove('C');
    for (int rowNum = 0; rowNum < rows; rowNum++)
    {
        for (int colNum = 0; colNum < columns; colNum++)
        {
            if(gamePad[rowNum][colNum]->getSpecies() == 'C')
            {
                gamePad[rowNum][colNum]->breed(gamePad);
            }
        }
    }
}

/**
 * Move the critters with species
 * GamePad::simulateMove
 * @param species : the species of critter.
 */
void GamePad::simulateMove(char species)
{
    for (int rowNum = 0; rowNum < rows; rowNum++)
    {
        for (int colNum = 0; colNum < columns; colNum++)
        {
            if(gamePad[rowNum][colNum]->getSpecies() == species)
            {
                gamePad[rowNum][colNum]->move(gamePad);
            }
        }
    }
}


/**
 * Init the isMoved variable for the next move.
 * @brief GamePad::initIsAlreadyMoved
 */
void GamePad::initIsAlreadyMoved()
{
    for (int rowNum = 0; rowNum < rows; rowNum++)
    {
        for (int colNum = 0; colNum < columns; colNum++)
        {
           gamePad[rowNum][colNum]->setMoved(false);
        }
    }
}

/**
 * Mutate ant to poisonous ant.
 * @brief GamePad::mutateAnt2Poison
 * @param pos : position to be mutated
 */
void GamePad::mutateAnt2Poison(Position * pos)
{
    delete gamePad[pos->getXPos()][pos->getYPos()];
    gamePad[pos->getXPos()][pos->getYPos()] = new PoisonousAnt(pos, 0);
}
