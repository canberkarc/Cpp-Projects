#include "Player.h"

/**
 * The contructor
 * Player::Player
 */
Player::Player(int ants, int doodlebugs)
{
    //Create game pad
    gamePad = new GamePad(ants, doodlebugs);
}

/**
 * Start simulation.
 * Player::start
 */
void Player::start(){
    char ENTER;
    //Show firstly.
    gamePad->showGamePad();
    //variable for the step number.
    int stepNumber = 0;
    cout << "Game started" << endl;
    while (cin.get(ENTER)) // whenever the "ENTER" button is pressed..
    {
        step();
        stepNumber ++;
        cout << "Step Number = " << stepNumber << endl;
        cout << "Please press enter for next time step." << endl;
    }
}

/**
 * Run this function every time enter pressed.
 * Player::step
 */
void Player::step()
{    
    //runs simulation.
    gamePad->simulate();
    //repaint the game pad.
    gamePad->showGamePad();
}
