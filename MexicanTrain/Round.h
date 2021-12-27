/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#pragma once
#include"Deck.h"
#include"Human.h"
#include"Computer.h"
#include<vector>

using namespace std; 

//work around for circular include dependency, got this solution from StackOverFlow.
class Game;

class Round
{
public:

	//round contructor
	Round();

	//round destructor
	~Round() {};

	//getter for round number
	int GetRound() { return mRoundNumber; };

	//setter for round #
	void SetRound(int a_RoundNumber) { mRoundNumber = a_RoundNumber; };

	//returns engine index for the current round
	int GetEngineIndex();

	//setter for boneyard tile vectors
	void SetBoneYard(std::vector<Tile> a_BoneYard) { mBoneYard = a_BoneYard; };

	//initializes a new round
	void InitializeRound(Game* a_gameObject);

	//prints boneyard
	void PrintBoneYard();

	//tosses a coin before a new round if score is draw
	void TossACoin();

	//getter for human score
	int GetHumanScore() { return mHumanScore; };

	//getter for computer score
	int GetComputerScore() { return mComputerScore; };

	//prints the entire game scene on console all the time
	void PrintScene(Human a_HumanPlayer, Computer a_ComputerPlayer, Tile a_Engine, Game a_gameObject);

	//creates a vector of tile from vector of string
	vector<Tile> CreateTilesVector(int a_startIndex, string a_endString, vector<string> a_stringVector, string a_tileFor);

	//saves game to a file
	void SaveGame(Human a_HumanPlayer, Computer a_ComputerPlayer, Tile a_engine, int a_PlayerIndex, Game& a_gameObject);

	//starts game from a file
	void StartGameFromFile(Human& a_HumanPlayer, Computer& a_ComputerPlayer, Game& a_gameObject);

private:

	int mRoundNumber;
	int mEngineIndex;
	int mHumanScore;
	int mComputerScore;
	string mGameState;
	bool mTurnHuman, mTurnComputer;
	std::vector<Tile> mBoneYard;
	Deck mDeck;
	Train mMexicanTrain, mHumanTrain, mComputerTrain;
};

