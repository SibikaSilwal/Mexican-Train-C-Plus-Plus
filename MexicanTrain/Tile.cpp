/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#include "Tile.h"
#include<iostream>

/* *********************************************************************
Function Name: Tile
Purpose: To construct a tile object
Parameters: left pip , right pip integer values for the tile
Return Value: none
Algorithm:
		1) left and right pip values assignment to the tiles mTileLeft and mTileRight variable
Assistance Received: none
********************************************************************* */

Tile::Tile(int a_TileLeft, int a_TileRight) {
	mTileLeft = a_TileLeft;
	mTileRight = a_TileRight;
}

/* *********************************************************************
Function Name: IsDoubleTile
Purpose: to check if a tile is a double tile
Parameters: none
Return Value: true or false
Algorithm:
		1) if right and left pips of a tile are equal, tile is a double tile
			therefore return true else false

Assistance Received: none
********************************************************************* */

bool Tile::IsDoubleTile() {

	if (GetTileLeft() == GetTileRight()) {
		return true;
	}

	return false;
}


/* *********************************************************************
Function Name: MakeTile
Purpose: to create a tile object from a given string
Parameters: a_TileString- string to generate a tile from, a_tilefor : string identifier
Return Value: a tile object
Algorithm:
		1) char to int conversion

Assistance Received: StackOverFlow Forum
********************************************************************* */

Tile Tile::MakeTile(std::string a_TileString, std::string a_TileFor) {

	if (a_TileString == "M") {
		return Tile(-2, -2);
	}
	if (a_TileFor == "C-train") {
		// char to int conversion : referred to stackoverflow forum for this conversion technique
		int tileLeft = a_TileString[2] - '0'; 
		int tileRight = a_TileString[0] - '0';
		return Tile(tileLeft, tileRight);
	}
	// char to int conversion : referred to stackoverflow forum for this conversion technique
	int tileLeft = a_TileString[0] - '0'; 
	int tileRight = a_TileString[2] - '0';
	return Tile(tileLeft, tileRight);
}