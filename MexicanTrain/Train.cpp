/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#include "Train.h"
#include<iostream>

using namespace std;

/* *********************************************************************
Function Name: Train
Purpose: to construct a train object, initializes all the member variables
Parameters: none
Return Value: none
Algorithm:
		1) none
Assistance Received: none
********************************************************************* */

Train::Train() {
	mTrainName = "DefaultTrain";
	mTrain = {};
	mTrainMarker = false;
}

/* *********************************************************************
Function Name: GetTrainLastTile
Purpose: returns the last tile of a train
Parameters: engine for the round
Return Value: Tile object
Algorithm:
		1) conditional statement: if the train is an empty train return 
			the engine otherwise return the last element of the train
			vector

Assistance Received: none
********************************************************************* */

Tile Train::GetTrainLastTile(Tile a_Engine){ 
	if(mTrain.size()>0)
		return mTrain[mTrain.size() - 1]; 

	return a_Engine;
}

/* *********************************************************************
Function Name: IsOrphDoubleTrain
Purpose: to determine if a train is orphan double train
Parameters: none
Return Value: true or false
Algorithm:
		1)conditional statement: if the train is an empty train return 
			false otherwise check if last tile is double tile, if yes
			return true otherwise false

Assistance Received: none
********************************************************************* */

bool Train::IsOrphDoubleTrain() {

	int lastIndex = GetTrain().size() - 1;

	if (lastIndex < 0) {
		return false;
	}
	if (GetTrain()[lastIndex].IsDoubleTile()) {
		return true;
	}

	return false;
}


/* *********************************************************************
Function Name: AddTileOnTrain
Purpose: to add tile at the end of a train
Parameters: tile object to be added to the train
Return Value: none
Algorithm:
		1) add tile to the end of train i.e. tiles vector

Assistance Received: none
********************************************************************* */

void Train::AddTileOnTrain(Tile a_tile) {
	mTrain.push_back(a_tile);
}