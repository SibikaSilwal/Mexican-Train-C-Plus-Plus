/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#pragma once
#include<vector>
#include<string>
#include"Tile.h"

class Train
{
public:

	//train constructor
	Train();

	//train destructor
	~Train() {};

	//sets train's name eg: "H-train", "M-train"
	void SetTrainName(std::string a_name) { mTrainName = a_name; };

	//gets train name
	std::string GetTrainName() { return mTrainName; };

	//adds tile to the end of the train (vector of tiles)
	void AddTileOnTrain(Tile a_tile);

	//returns the train i.e. the vector of tiles for the train
	std::vector<Tile> GetTrain() { return mTrain; };

	//returns last tile of a train
	Tile GetTrainLastTile(Tile a_Engine);
	
	//updates the train marker to true or false
	void UpdateTrainMarker(bool a_marker) { mTrainMarker = a_marker; }

	//returns the train marker value
	bool TrainHasMarker() { return mTrainMarker; };
	
	//determines if a train is an orphan train
	bool IsOrphDoubleTrain();

private:
	//train's name
	std::string mTrainName;

	//the actual train which is a vector of tiles
	std::vector<Tile> mTrain;

	//train's marker
	bool mTrainMarker;
};

