/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#pragma once
#include<string>
class Tile
{

public:

	//tile contructor
	Tile(int a_TileLeft, int a_TileRight);

	//tile destructor
	~Tile() {};

	//getter for tile left pip value
	int GetTileLeft() { return mTileLeft; };

	//setter for tile left pip value
	void SetTileLeft(int a_left) { mTileLeft = a_left; };

	//getter for tile right pip value
	int GetTileRight() { return mTileRight; };

	//setter for tile right pip value
	void SetTileRight(int a_right) { mTileRight = a_right; };

	//checks if the tile is a double tile
	bool IsDoubleTile();

	//prints tile normally left-right
	std::string PrintTile() { 
		std::string tile = std::to_string(mTileLeft) + "-" + std::to_string(mTileRight);
		return  tile; };

	//prints tile in reverse right-left
	std::string PrintTileReverse() {
		std::string tile = std::to_string(mTileRight) + "-" + std::to_string(mTileLeft);
		return  tile;
	};

	//makes tile from passed string
	Tile MakeTile(std::string a_TileString, std::string a_TileFor);

private:

	int mTileLeft;
	int mTileRight;
};

