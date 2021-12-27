/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#pragma once
#include<vector>
#include<string>
#include<map>
#include<iostream>
#include"Tile.h"
#include"Train.h"

using namespace std;
class Player
{
public:

	//player class contructor
	Player();

	//player class destructor
	~Player() {};

	//getter for player score
	int GetPlayerScore(vector<Tile> a_PlayerHand);

	//returns vector of orphan trains
	std::vector<Train*> GetOrpDblTrain(std::vector<Train*> a_trains);

	//finds eligible trains for player
	virtual std::vector<Train *> FindEligibleTrains(bool a_HTrainMarker, bool a_CTrainMarker, Train &a_Htrain, Train &a_Ctrain, Train &a_Mtrain);

	//makes player pick a train
	virtual Train* PickAtrain(std::vector<Train *> a_EligibleTrains, Tile a_Engine);

	//checks if player has playable tile
	virtual bool CheckPlayableTile(std::vector<Train *> a_EligibleTrains, Tile a_Engine) { return false; };

	//makes player draw a tile
	virtual map<int, Tile> DrawTile(std::vector<Tile>& a_Boneyard);

	//makes player pick a tile
	virtual map<int, Tile> PickATile(Train * a_PickedTrain, Tile a_Engine);
	
	//validated the tile being placed on a train
	Tile ValidateTile(Tile a_PlayingTile, Tile a_LastTile);

	//removes played tile from player's hand
	virtual void RemoveTileFromHand(int a_index, Train* a_PlayedTrain, Tile a_PlayedTile) {};

	//makes player make a draw move when they dont have playable tile in their hand
	void DrawMove(vector<Train*> a_EligibleTrains, Tile a_Engine, vector<Tile>& a_Boneyard, Train& a_CTrain, Train& a_Htrain);

	//allows player to make move in their turn
	void MakeMove(Tile a_engine, Train& a_Htrain, Train& a_Ctrain, Train& a_Mtrain, vector<Tile>& a_Boneyard, string &a_gameState);

	//adds marker to player's personal train
	virtual bool AddMarker(Tile a_drawnTile, std::vector<Train*> a_EligibleTrains, Tile a_Engine, Train& a_CTrain, Train& a_Htrain) {
		return false;
	};

	//returns the number of times the player played a double tile in a turn
	virtual int GetPlayedDoubleCount() { return 0; }

	//determines if a player can play again
	virtual bool CanPlayAgain() { return false; }

	//determines if the player has to play OD in a turn
	virtual bool HasToPlayOD() { return true; }

	//determines if the player hand is empty
	virtual bool PlayerHandEmpty() { return false; };

	//gets the players hand i.e. the vector of tiles
	virtual vector<Tile> GetPlayerHand() { return vector<Tile>{}; }

	//displays menu before each player's turn
	virtual string DisplayMenu(vector<Train*> a_EligibleTrains, Tile a_Engine) { return "nothing"; };

	//determines if a player can play double tile while picking a tile
	bool CanPlayDoubleTile(vector<Train*> a_EligibleTrains, map<int, Tile> a_PickedTileMap, Train PickedTrain, vector<Tile> a_PlayerHand, Tile a_Engine);

	/*Strategy functions*/

	//finds the largest playable tile from players hand
	map<int, Tile> FindLargestTileIndex(int a_endTilePips, std::vector<Tile> a_PlayerHand );

	//finds a double playable time from players hand
	map<int, Tile> FindDoubelTile(Train a_eligTrain, std::vector<Tile> a_PlayerHand, Tile a_Engine);

	//determines if a player can make an orphan train in a turn
	map<string, string> MakeOrphanTrain(vector<Train*> a_EligibleTrains, vector<Tile> a_PlayerHand, Tile a_Engine);
	
	//checks if the player has playable tiles for a picked train
	bool HasPlayableTile(Train a_pickedTrain, std::vector<Tile> a_PlayerHand, Tile a_Engine);

	//helps human for their next move
	void HelpHuman(vector<Train*> a_EligibleTrains, vector<Tile> a_HumanHand, Tile a_Engine);

	//sets the Computers strategy messages
	void SetExplanation(string a_message) { mExplainTurn = a_message; };

	//Prints strategy used by computer after computer's turn
	void PrintGameStrategy();

	//print human help messages, given the messages
	void PrintHumanHelp(string a_tile, string a_trainName, string a_message) {
		cout << "I suggest you to play " << a_tile << " on " << a_trainName
			<< " because " << a_tile << a_message << endl;
	}

private:

	//Computer's strategy
	string mExplainTurn;
};

