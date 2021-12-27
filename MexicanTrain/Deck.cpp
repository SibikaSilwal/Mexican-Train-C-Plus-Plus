/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#include "Deck.h"
#include<stdio.h>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>

using namespace std;

/* *********************************************************************
Function Name: Deck
Purpose: To construct a Deck Object and to generate and populate the mDeck
		 member vector with 55 unique tiles
Parameters:none
Return Value: none
Algorithm:
		1) Since there are 55 tiles, each tile going from 0 to 9, 1 to 9, and so on
		this function used a nested for loop to generate the 55 tiles.
	    2) Each tile generated is added to the end of the mDeck vector which is a
		vector of tiles.
Assistance Received: none
********************************************************************* */

Deck::Deck() {
	
	for (int i = 0; i <= 9; i++) {
		for (int j = i; j <= 9; j++) {
			mDeck.push_back(Tile(i, j));
		}
	}	
}


/* *********************************************************************
Function Name: PlaceEngine
Purpose: To get the engine tile for each round
Parameters: a_EngineIndex, which an integer value that represent the 
			index of the engine tile in mDeck vector of tiles
Return Value: the engine Tile
Algorithm:
		1) Gets the tile for the given index from mDeck vector,
			erases the tile fomr mDeck vector and 
			returns the Tile (engine tile) as a return value.
Assistance Received: none
********************************************************************* */

Tile Deck::PlaceEngine(int a_EngineIndex) {
	
	Tile engineTile = mDeck[a_EngineIndex];

	//delete the engine tile from the deck
	mDeck.erase(mDeck.begin() + a_EngineIndex);

	return engineTile;

}


/* *********************************************************************
Function Name: ShuffleDeck
Purpose: To shuffle the deck of tiles before dealing them so that in each
			round players get different set of tiles
Parameters: none
Return Value: none
Algorithm:
		1) using a for loop generated two random numbers 26 times, which is
			half of the size of the tile in deck to be dealt, for the two numbers
			generated swaps the Tiles of those two indexes
		2) If the two random numbers were same does not do anything.
Assistance Received: none
********************************************************************* */

void Deck::ShuffleDeck() {
	//seed for random number generator 
	srand(time(0));
	int swapIndex1, swapIndex2;
	for (int i = 0; i < 27; i++) {
		swapIndex1 = rand() % 54;
		swapIndex2 = rand() % 54;
		if (swapIndex1 != swapIndex2) {
			swap(mDeck[swapIndex1], mDeck[swapIndex2]);
		}
	}
}

/* *********************************************************************
Function Name: DealDeck
Purpose: To distribute 16 tiles each to human and computer player and add the
		 remaining 22 tiles to the boneyard
Parameters: a human object, a computer object and a boneyard i.e. vectors of
			tiles accepted all by reference. They are the actual human player 
			object playing, Computer object playing, and the boneyard of the
			round.
Return Value: none
Algorithm:
		1) Deals the shuffle tile to human player and computer player by
			adding tiles in human hand and computer hand
		2) After dealing tiles to players, adds remaining tile to the 
			boneyard vector.
Assistance Received: none
********************************************************************* */

void Deck::DealDeck(Human& a_Human, Computer& a_Computer, std::vector<Tile> &a_Boneyard) {

	//temporary vector to hold the players tiles
	vector<Tile> a_HumanHand = {}; vector<Tile> a_ComputerHand = {};

	//sum of the tiles to be dealt to both players
	int playersHand = 32;

	//boneyard size
	int boneYard = mDeck.size() - playersHand;

	for (int i = 0; i < playersHand; i+=2) {
		a_HumanHand.push_back(mDeck[i]);
		a_ComputerHand.push_back(mDeck[i + 1]);
	}
	for (int i = playersHand; i < (boneYard+playersHand) ; i++) {
		a_Boneyard.push_back(mDeck[i]);
	}
	//assigning the temporary a_humanhand vector to humanhand using its setter
	a_Human.SetHumanHand(a_HumanHand);
	//assigning the temporary a_Computerhand vector to computerhand using its setter
	a_Computer.SetComputerHand(a_ComputerHand);
	
	//deleting all the tiles from the deck
	mDeck.clear();
}