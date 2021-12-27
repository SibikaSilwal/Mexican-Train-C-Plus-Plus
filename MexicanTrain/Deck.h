/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#pragma once
#include<vector>
#include<stdio.h>
#include"Tile.h"
#include"Human.h"
#include"Computer.h"
#include<iostream>
#include<string>

using namespace std;
class Deck
{
public:

	//constructor of the class
	Deck();

	//destructor of the class
	~Deck() {};

	//gets the engne tile for a round
	Tile PlaceEngine(int a_EngineIndex);

	//shuffles the deck of tile before dealing
	void ShuffleDeck();

	//deals the tiles to players and adds remaining tiles to the boneyard before each fresh round
	void DealDeck(Human& a_Human, Computer& a_Computer, std::vector<Tile> &a_Boneyard);
	
private:

	//a private vector of tiles which represent the deck and stores all 55 tiles before being dealt
	std::vector<Tile> mDeck;
};

