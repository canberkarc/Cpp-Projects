#include "Player.h"

//Global variable

//The number of rows on the game pad
extern const int ROWS = 15;
//The number of columns on the game pad
extern const int COLUMNS = 20;
//The number of Ants initially
extern const int ANTS = 100;
//The number of Doodlebugs initially
extern const int DOODLEBUGS = 5;


int main()
{
    //Start game
    Player * player = new Player(ANTS, DOODLEBUGS);
    player->start();
    return 0;
}
