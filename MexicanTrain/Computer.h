/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#pragma once
#include "Player.h"
#include"Tile.h"
#include<vector>

using namespace std;

class Computer :
    public Player
{
public:

    //computer class constructor
    Computer();

    //computer class destructor
    ~Computer() {};

    //setter for computerHand tiles
    void SetComputerHand(std::vector<Tile> a_ComputerHand) { mComputerHand = a_ComputerHand; };

    //display computerhand on screen
    void PrintComputerHand();

    //find computer's eligible trains
    virtual std::vector<Train *> FindEligibleTrains(bool a_HTrainMarker, bool a_CTrainMarker, Train& a_Htrain, Train& a_Ctrain, Train& a_Mtrain);
    
    //make computer pick a train
    virtual Train* PickAtrain(std::vector<Train *> a_EligibleTrains, Tile a_Engine);

    //check if computer has any playable tiles on its eligile trains
    virtual bool CheckPlayableTile(std::vector<Train*> a_EligibleTrains, Tile a_Engine);

    //make computer draw tile from boneyard
    virtual map<int, Tile> DrawTile(std::vector<Tile>& a_Boneyard);

    //add marker to computer train
    virtual bool AddMarker(Tile a_drawnTile, std::vector<Train*> a_EligibleTrains, Tile a_Engine, Train& a_CTrain, Train& a_Htrain);

    //make computer pick a tile
    virtual map<int, Tile> PickATile(Train* a_PickedTrain, Tile a_Engine); //need to do from here

    //Remove played tile from computer hand
    virtual void RemoveTileFromHand(int a_index, Train* a_PlayedTrain, Tile a_PlayedTile);

    //get the count for the #of times computer played a double tile in one turn
    virtual int GetPlayedDoubleCount() { return mplayedDblCount; }

    //check if computer can play again
    virtual bool CanPlayAgain();

    //check if computer has to play an orphan double train
    virtual bool HasToPlayOD() { return mHasToPlayOD; }


    //check if computer's hand is empty
    virtual bool PlayerHandEmpty();

    //getter for computer's hand
    virtual vector<Tile> GetPlayerHand() { return mComputerHand; }

    //display menu before computer's turn
    virtual string DisplayMenu(vector<Train*> a_EligibleTrains, Tile a_Engine);

    //update computer's info after playing a tile
    void UpdatePlayerInfo(Train* a_PlayedTrain, Tile a_PlayedTile);

private:
    
    //actual computer hand which is a vector of tiles
    std::vector<Tile> mComputerHand;

    //bool variable that stores if computer has to play an orphan double train
    bool mHasToPlayOD;

    //number of times computer played a double tile in a turn
    int mplayedDblCount;

    //strategy applied by the computer in a turn
    string mStrategy;
};

