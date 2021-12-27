/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#include "Computer.h"
#include"Human.h"
#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
#include<algorithm>

using namespace std;

/* *********************************************************************
Function Name: Computer
Purpose: to construct computer object
Parameters:none
Return Value: none
Algorithm: none
Assistance Received:none
********************************************************************* */
Computer::Computer() {
	mComputerHand = {};
	mHasToPlayOD = true;
	mplayedDblCount = 0;
}

/* *********************************************************************
Function Name: PrintComputerHand
Purpose: To display the computer hand tiles in the console
Parameters: none
Return Value: none
Algorithm: loop and print statement
Assistance Received: none
********************************************************************* */

void Computer::PrintComputerHand() {
	cout << mComputerHand.size() << endl;
	for (int i = 0; i < mComputerHand.size(); i++) {
		cout << i << "->[" << mComputerHand[i].GetTileLeft() << "-" << mComputerHand[i].GetTileRight() << "]  ";
		if (i == (mComputerHand.size() / 2)) cout << endl;
	}
	cout << endl;
}

/* *********************************************************************
Function Name: DisplayMenu
Purpose: Virtual functon: to display the options menu before each Computer turn
Parameters: vector of pointers of eligibleTrains, engine tile
Return Value: a string that denotes what option human player selected
Algorithm:
		1) user input
		2) input validation
		3) print statements
Assistance Received: none
********************************************************************* */

string Computer::DisplayMenu(vector<Train*> a_EligibleTrains, Tile a_Engine) {
	string userInput;
	cout << "\n>> Computer's Turn" << endl;
	cout << "----------------------" << endl;
	cout << "Please enter 'S' to save the game." << endl;
	cout << "Please enter 'Q' to quit the game. " << endl;
	cout << "Please enter 'M' to continue making moves. " << endl;

	cin >> userInput;
	transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

	while (userInput != "M" && userInput != "S" && userInput != "Q") {
		cout << "Please enter 'M', 'S', or 'Q'." << endl;
		cin >> userInput;
		transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
	}
	if (userInput == "S") {
		cout << "Saving the game..." << endl;
		return "save";
	}
	if (userInput == "Q") {
		cout << "Quiting the game..." << endl;
		return "quit";
	}
	return "play";
}

/* *********************************************************************
Function Name: FindEligibleTrains
Purpose: Virtual function, to find Computer's eligible trains in the case where
		 there is no orphan train
Parameters: htrain marker, ctrain marker, human, computer and mexican train by reference
Return Value: vector of pointers of eligible train for human
Algorithm:
		1) check if human train has marker
		2) if yes add that to the eligible train vector
		3) Otherwise add ctrain and mtrain references to the eligible trains vector
		4) return the vector
Assistance Received: none
********************************************************************* */

vector<Train *> Computer::FindEligibleTrains(bool a_HTrainMarker, bool a_CTrainMarker, Train& a_Htrain, Train& a_Ctrain, Train& a_Mtrain) {
	
	vector<Train *> eligTrains = { &a_Mtrain, &a_Ctrain };

	if (a_HTrainMarker) {
		eligTrains.push_back(&a_Htrain);
	}

	return eligTrains;
}

/* *********************************************************************
Function Name:CheckPlayableTile
Purpose: Virtual function to check if computer player has any playable tiles
		 on hand, to play on its eligible trains
Parameters: vector of pointers of eligibletrains, engine tile
Return Value: true if computer has playable tile else false
Algorithm:
		1) nested loop
		2) loop through all the eligible trains for human
		3) for each train, loop through the computerHand, and check if any tile
			in computer hand is playable in the eligible train
		4) if one playable tile found, return true, and do not loop further

Assistance Received: none
********************************************************************* */

bool Computer::CheckPlayableTile(std::vector<Train*> a_EligibleTrains, Tile a_Engine) {

	bool hasPlayableTile = false;
	for (int i = 0; i < a_EligibleTrains.size(); i++) {
		for (int j = 0; j < mComputerHand.size(); j++) {

			Tile playableTile = Player::ValidateTile(mComputerHand[j], a_EligibleTrains[i]->GetTrainLastTile(a_Engine));

			//if the computer player has atleast one tile on hand to play on one of the eligible trains, return true
			if (playableTile.GetTileLeft() != -1)return true;
		}
	}
	return hasPlayableTile;
}

/* *********************************************************************
Function Name: DrawTile
Purpose: virtual function: to let computer draw tile from boneyard, and add it
		 to computerHand, whch will be played immediatly if the tile is playable
Parameters: boneyard by reference
Return Value: map of the drawn tile, which has the tile index and tile object
Algorithm:
		1) store the first tile of boneyard as drawnTile in a tile object
		2) erase the first element of boneyard
		3) add the drawn tile to player's hand
		4) return the map of the drawn tile index in human hand, which is the last element,
			and the tile object
Assistance Received: none
********************************************************************* */

map<int, Tile> Computer::DrawTile(vector<Tile>& a_Boneyard) {

	//get the first tile from boneyard and erase it
	Tile drawnTile = a_Boneyard[0];
	a_Boneyard.erase(a_Boneyard.begin());

	//push the tile into computerhand which will be played immediately if possible
	mComputerHand.push_back(drawnTile);

	cout << "Computer drew a tile from boneyard: " << drawnTile.PrintTile() << endl;
	
	//a map of drawn tile and its index
	map<int, Tile> tileIndexMap;
	tileIndexMap.insert(pair<int, Tile>((mComputerHand.size() - 1), drawnTile));

	return tileIndexMap;
}

/* *********************************************************************
Function Name: AddMarker
Purpose: Virtual function to add marker to computer train if the drawn tile
		 could not be played
Parameters: drawntile, vector of eligtrain pointers, engine, ctrain and htrain
			by reference
Return Value: true of need to add marker, false otherwise
Algorithm:
		1) loops through the eligible trains vectors and checks if the drawn
			tile can be played in any of the trains
		2) if yes, returns false immediately
		3) If tile was not valid for any of the eligible trains, adds marker
			to computer train, sets the explanation to display on screen that
			computer could not play the turn
		4) If it was computer's turn again, makes sure that its updated

Assistance Received: none
********************************************************************* */

bool Computer::AddMarker(Tile a_drawnTile, std::vector<Train*> a_EligibleTrains, Tile a_Engine, Train& a_CTrain, Train& a_Htrain) {
	
	for (int i = 0; i < a_EligibleTrains.size(); i++) {

		//drawntile(-5,-5) means boneyard was empty
		if (a_drawnTile.GetTileLeft() == -5) break;

		Tile isValidTile = Player::ValidateTile(a_drawnTile, a_EligibleTrains[i]->GetTrainLastTile(a_Engine));

		//if the player has atleast one tile on hand to play on one of the eligible trains, return true
		if (isValidTile.GetTileLeft() != -1) {
			return false;
		}
	}
	
	mHasToPlayOD = true;
	a_CTrain.UpdateTrainMarker(true);
	Player::SetExplanation("Computer did not play any tile because the drawn tile "+ a_drawnTile.PrintTile() +"  was not playable.");
	mplayedDblCount = 0; // making sure, its not computer player's turn again, if it was
	return true;
}

/* *********************************************************************
Function Name: PickAtrain
Purpose: Virtual function to allow make computer pick a train to place tile on
		 from it's eligigble trains
Parameters: vector of Eligible trains pointer, engine tile
Return Value: Picked train pointer
Algorithm:
		1) Make bool variables for all trains and set to true if computer can 
			play the trains and has tile to play on them
		2) From all the playable trains, priotize the train that can make an 
			orphan train, if such train found return the train and return from
			the function
		3) If can't make orphan trian, see if human's train has marker, if yes 
			play in human train
		4) Check if mexican train was started already, if not return mexican train
		5) Check which train can play a double tile, return the train that can
		6) If none of the above conditions were possible, return the train that can
			play the largest pip tile among the eligible trains

Assistance Received: none
********************************************************************* */

Train* Computer::PickAtrain(vector<Train *> a_EligibleTrains, Tile a_Engine) {

	int hTrainIndex = -1; int mTrainIndex = -1; int cTrainIndex = -1;
	bool canPlayHTrain = false; bool canPlayMTrain = false; bool canPlayCTrain = false;
	int playableTrainCount = 0;

	for (int i = 0; i < a_EligibleTrains.size(); i++) {
		if (a_EligibleTrains[i]->GetTrainName() == "H-Train") {
			hTrainIndex = i;
			if (Player::HasPlayableTile(*a_EligibleTrains[hTrainIndex], mComputerHand, a_Engine)) {
				canPlayHTrain = true;
				playableTrainCount++;
			}
		}			
		if (a_EligibleTrains[i]->GetTrainName() == "M-Train") {
			mTrainIndex = i;
			if (Player::HasPlayableTile(*a_EligibleTrains[mTrainIndex], mComputerHand, a_Engine)) {
				canPlayMTrain = true;
				playableTrainCount++;
			}
		}			
		if (a_EligibleTrains[i]->GetTrainName() == "C-Train") {
			cTrainIndex = i;
			if (Player::HasPlayableTile(*a_EligibleTrains[cTrainIndex], mComputerHand, a_Engine)) {
				canPlayCTrain = true;
				playableTrainCount++;
			}
		}
	}

	//First priority: Pick a train that can make an orphan train if possible
	map<string, string> makeOrphan = Player::MakeOrphanTrain(a_EligibleTrains, mComputerHand, a_Engine);
	if (makeOrphan.find("possible")->second == "yes") {
		mStrategy = " was the double tile on hand which can make an orphan train and force opponent to play on it.";
		for (int i = 0; i < a_EligibleTrains.size(); i++) {
			if (a_EligibleTrains[i]->GetTrainName() == makeOrphan.find("trainName")->second) return a_EligibleTrains[i];
		}
	}
	//h-train second priority if eligible and has tiles to play on it:
	if (canPlayHTrain) {
		if (playableTrainCount > 1 && a_EligibleTrains[hTrainIndex]->IsOrphDoubleTrain()) {
			//don't pick this train
		}
		else if (playableTrainCount == 1 && a_EligibleTrains[hTrainIndex]->IsOrphDoubleTrain()) {
			mStrategy = " was the largest tile on hand and opponent's train was an Orphan Train. ";
			return a_EligibleTrains[hTrainIndex];
		}
		else {
			mStrategy = " was the largest tile on hand and opponent's train had a marker. ";
			return a_EligibleTrains[hTrainIndex];
		}
	}

	//m-train third priority if it is not started already
	if (canPlayMTrain) {
		if (a_EligibleTrains[mTrainIndex]->GetTrain().size() == 0) {
			mStrategy = " was the largest tile on hand and Mexican train was not started yet. ";
			return a_EligibleTrains[mTrainIndex];
		}
	}

	if (playableTrainCount > 1) {
		if (canPlayMTrain && a_EligibleTrains[mTrainIndex]->IsOrphDoubleTrain()) {
			mStrategy = " was the largest tile that could be played leaving Mexican Train as an orphan train.";
			if (canPlayCTrain) return a_EligibleTrains[cTrainIndex];
			if (canPlayHTrain) return a_EligibleTrains[hTrainIndex];
		}
		if (canPlayCTrain && a_EligibleTrains[cTrainIndex]->IsOrphDoubleTrain()) {
			mStrategy = " was the largest tile that could be played leaving Computer Train as an orphan train.";
			if (canPlayMTrain) return a_EligibleTrains[mTrainIndex];
			if (canPlayHTrain) return a_EligibleTrains[hTrainIndex];
		}
	}

	//If no orphan train can be made pick from mtrain or ctrain 

	int mTrainPips, cTrainPips;
	
	//if both m-train and c-train are available, and m-train was already started before, compare the pips for two trains
	if (canPlayMTrain && canPlayCTrain) 
	{
		mTrainPips = a_EligibleTrains[mTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight();
		cTrainPips = a_EligibleTrains[cTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight();

		Tile MTile = Player::FindLargestTileIndex(mTrainPips, mComputerHand).begin()->second;
		Tile CTile = Player::FindLargestTileIndex(cTrainPips, mComputerHand).begin()->second;

		mStrategy = " was the largest tile that could be played in this turn among all the eligible trains.";

		if ((MTile.GetTileLeft() + MTile.GetTileRight()) >= (CTile.GetTileLeft() + CTile.GetTileRight())) {
			return a_EligibleTrains[mTrainIndex];
		}
		else {
			return a_EligibleTrains[cTrainIndex];
		}

	}

	//if can't compare tiles on mtrain and ctrain because of available tiles, prioritize mtrain then ctrain

	mStrategy = " was the largest tile that could be played in this turn among all the eligible trains.";

	if (canPlayMTrain) return a_EligibleTrains[mTrainIndex];

	if (canPlayCTrain) return a_EligibleTrains[cTrainIndex];


	cout << "ALERT!!!!! Picked the default train" << endl;
	return a_EligibleTrains[0]; //default, should not get here
	
}

/* *********************************************************************
Function Name:PickATile
Purpose: Virtual function to make computer pick a tile to place on the
		 picked train
Parameters: pointer of the picked train, engine tile
Return Value: a map of the index of picked tile and the tile object
Algorithm:
		1) From the picked tile, search for a double playable tile
		2) if double tile found, return the double tile map with
			tile index and tile object
		3) else return the largest pip tile map with
			tile index and tile object

Assistance Received: none
********************************************************************* */

map<int, Tile> Computer::PickATile(Train* a_PickedTrain, Tile a_Engine) {

	int endTilePips = a_PickedTrain->GetTrainLastTile(a_Engine).GetTileRight();

	int tileIndex;

	int doubleTileIndex = Player::FindDoubelTile(*a_PickedTrain, mComputerHand, a_Engine).begin()->first;

	//if playable double tile is found, play double tile, else play the largest pips tile
	if (doubleTileIndex != -1) {
		tileIndex = doubleTileIndex;
		
		if(mStrategy==" was the largest tile that could be played in this turn among all the eligible trains.")
			mStrategy = " was the double tile that could be played in this turn.";
	}
	else {
		tileIndex = Player::FindLargestTileIndex(endTilePips, mComputerHand).begin()->first;
	}

	Tile pickedTile = mComputerHand[tileIndex];

	map<int, Tile> TileIndexMap;
	TileIndexMap.insert(pair<int, Tile>(tileIndex, pickedTile));

	cout << left << setw(10) << " ";
	
	return TileIndexMap;
	
}

/* *********************************************************************
Function Name: RemoveTileFromHand
Purpose: Virtual function to delete the played tile from computer's hand
Parameters: picked tile index, played train, played tile object
Return Value: none
Algorithm:
		1) erase the element of the given index from computerHand
		2) call updatePlayerInfo function which updates the state of
			the player after playing a tile in a turn

Assistance Received: none
********************************************************************* */

void Computer::RemoveTileFromHand(int a_index, Train* a_PlayedTrain, Tile a_PlayedTile) {
	mComputerHand.erase(mComputerHand.begin() + a_index);
	UpdatePlayerInfo(a_PlayedTrain, a_PlayedTile);
	string message = "The computer chose to play " + a_PlayedTile.PrintTile() + " on " + a_PlayedTrain->GetTrainName() +
		" because " + a_PlayedTile.PrintTile() + " " + mStrategy;
	Player::SetExplanation(message);
}

/* *********************************************************************
Function Name: UpdatePlayerInfo
Purpose: to update players state after playing a tile in a turn
Parameters: played train pointer, played tile
Return Value: none
Algorithm:
		1) if computer played on its own train, update train marker to be false
			i.e. remove marker from computer train if there was one
		2) Check if the played tile was double, is yes increase playedDblCount
			by one and set HasToPlayOD variable to false, since the player
			does not have to play the double tile immediately after
		3) If played tile was not double set the mPlayedDbl count back to 0,
			set HasToPlayOD to truw, which denotes that computer has to play the
			orphan double train in next turn

Assistance Received: none
********************************************************************* */
void Computer::UpdatePlayerInfo(Train* a_PlayedTrain, Tile a_PlayedTile) {
	if (a_PlayedTrain->GetTrainName() == "C-Train") {
		a_PlayedTrain->UpdateTrainMarker(false);
	}
	if (a_PlayedTile.IsDoubleTile()) {
		mplayedDblCount = mplayedDblCount + 1;
		mHasToPlayOD = false;
	}
	else {
		mplayedDblCount = 0;
		mHasToPlayOD = true;
	}
}


/* *********************************************************************
Function Name: CanPlayAgain
Purpose: Virtual function that denotes if the computer can play again in the
		 same turn
Parameters:none
Return Value: true if can play again, false otherwise
Algorithm:
		1) If computer had played a double tile either once or twice, the
		player can play again
		2) If double tile was not played cannot play again

Assistance Received: none
********************************************************************* */

bool Computer::CanPlayAgain() {
	if (GetPlayedDoubleCount() == 1 || GetPlayedDoubleCount() == 2) {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: PlayerHandEmpty
Purpose: Virtual function to check if the players hand is empty
Parameters:none
Return Value: true or false
Algorithm:
		1) if computerhand size is 0 returns true otherwise false

Assistance Received: none
********************************************************************* */
bool Computer::PlayerHandEmpty() {
	if (mComputerHand.size() == 0) {
		return true;
	}
	return false;
}