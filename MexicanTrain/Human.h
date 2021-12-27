/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#pragma once
#include "Player.h"
#include"Tile.h"
#include"Computer.h"
#include<vector>
#include<string>

using namespace std;

class Human :
    public Player
{
public:

    //Human Class constructor
    Human();

    //Human Class Destructor
    ~Human() {};

    //Setter for humanHand vector of tiles
    void SetHumanHand(std::vector<Tile> a_HumanHand) { mHumanHand = a_HumanHand; };

    //Display the human tiles on screen
    void PrintHumanHand();
    
    //Finds eligible trains for human player
    virtual std::vector<Train *> FindEligibleTrains(bool a_HTrainMarker, bool a_CTrainMarker, Train& a_Htrain, Train& a_Ctrain, Train& a_Mtrain);

    //Checks if the player has playable tiles in the eligible trains
    virtual bool CheckPlayableTile(std::vector<Train*> a_EligibleTrains, Tile a_Engine);
    
    //lets player draw tile from boneyard
    virtual map<int, Tile> DrawTile(std::vector<Tile>& a_Boneyard);

    //adds marker to human train
    virtual bool AddMarker(Tile a_drawnTile, std::vector<Train*> a_EligibleTrains, Tile a_Engine, Train& a_CTrain, Train& a_Htrain);

    //allows user to pick a train to place a tile on
    virtual Train* PickAtrain(std::vector<Train *> a_EligibleTrains, Tile a_Engine);

    //allows user to pick a tile to place on the train
    virtual map<int, Tile> PickATile(Train* a_PickedTrain, Tile a_Engine);

    //removes tile from human hand
    virtual void RemoveTileFromHand(int a_index, Train* a_PlayedTrain, Tile a_PlayedTile);

    //returns the count for the double tiles played by human in the turn
    virtual int GetPlayedDoubleCount() { return mplayedDblCount; }

    //determines if the human player can play again in the same turn
    virtual bool CanPlayAgain();

    //determines if the human has to play the orphan double train
    virtual bool HasToPlayOD() { return mHasToPlayOD; }

    //checks if player hand is empty
    virtual bool PlayerHandEmpty();

    //getter for human hand
    virtual vector<Tile> GetPlayerHand() { return mHumanHand; }

    //displays the menu before each human turn
    virtual string DisplayMenu(vector<Train*> a_EligibleTrains, Tile a_Engine);

    //updates player info after playing a tile
    void UpdatePlayerInfo(Train* a_PlayedTrain, Tile a_PlayedTile);

    //determines if the picked train is elegible and/or human has a tile to play on it or not
    int isGoodTrain(std::vector<Train*> a_EligibleTrains, Tile a_Engine, std::string a_TrainName);

private:
    
    //actual human hand which is a vector of tiles
    std::vector<Tile> mHumanHand;
    //bool variable that tells if human player is required to play the orphan double train
    bool mHasToPlayOD;
    //count for the # of time human playes a double tile in a turn
    int mplayedDblCount;
};

