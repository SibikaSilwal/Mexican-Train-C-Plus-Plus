/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#include "Game.h"

/* *********************************************************************
Function Name: Game
Purpose: to contruct game object. Initializes all member variables
Parameters: none
Return Value: none
Algorithm:none

Assistance Received: none
********************************************************************* */
Game::Game() {
	mGameRound = 1;
	mGameScoreHuman = 0;
	mGameScoreComputer = 0;
}

/* *********************************************************************
Function Name: StartGame
Purpose: to start a new game after the program is launched
Parameters: a pointer of the game class object which is passed to the 
			round class. The game object is used for when a game is loaded
			from a file
Return Value: nonw
Algorithm:none

Assistance Received: none
********************************************************************* */
void Game::StartGame(Game* a_gameObject) {
	cout << " \n....Welcome to Mexican Train....\n " << endl;
	mRound.InitializeRound(a_gameObject);
	mGameScoreHuman = mGameScoreHuman + mRound.GetHumanScore();
	mGameScoreComputer = mGameScoreComputer + mRound.GetComputerScore();
	mGameRound = mRound.GetRound();
}

/* *********************************************************************
Function Name: ContinueGame
Purpose: To continue game after a round completes, and play another round
Parameters: Game object passed to the round class
Return Value: none
Algorithm: gameRound # incremented by 1

Assistance Received: none
********************************************************************* */
void Game::ContinueGame(Game* a_gameObject) {

    mGameRound = mGameRound + 1;
    Round NextRound; 
    NextRound.SetRound(mGameRound);
    NextRound.InitializeRound(a_gameObject);
        
}