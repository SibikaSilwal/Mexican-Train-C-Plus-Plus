/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#pragma once
#include"Round.h"

class Game
{
public:

	//game class constructor
	Game();

	//game class destructor
	~Game() {};

	//start a new game
	void StartGame(Game *a_gameObject);

	//continue the playing game
	void ContinueGame(Game *a_gameObject);

	//getter for human score
	int GetHumanScore() { return mGameScoreHuman; };

	//getter for computer score
	int GetComputerScore() { return mGameScoreComputer; };

	//setter for human score
	void SetHumanGameScore(int a_score) { mGameScoreHuman = a_score; };

	//setter for computer score
	void SetComputerGameScore(int a_score) { mGameScoreComputer = a_score; };

private:

	//round #
	int mGameRound;

	//game scores
	int mGameScoreHuman;
	int mGameScoreComputer;

	//round class object
	Round mRound;
};

