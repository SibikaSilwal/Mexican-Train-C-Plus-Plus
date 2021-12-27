/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#include "Human.h"
#include<iostream>
#include<algorithm>

using namespace std;

/* *********************************************************************
Function Name: Human
Purpose: to construct human class object. Initializes all member variables
Parameters:none
Return Value: none
Algorithm:none
Assistance Received: none
********************************************************************* */
Human::Human() {
	mHumanHand = {};
	mHasToPlayOD = true;
	mplayedDblCount = 0;
}

/* *********************************************************************
Function Name: PrintHumanHand
Purpose: To display the human hand tiles in the console
Parameters: none
Return Value: none
Algorithm: loop and print statement
Assistance Received: none
********************************************************************* */

void Human::PrintHumanHand() {
	cout << mHumanHand.size() << endl;
	for (int i = 0; i <mHumanHand.size(); i++) {
		cout << i << "->[" << mHumanHand[i].GetTileLeft() << "-" << mHumanHand[i].GetTileRight() << "]  ";
		if (i == (mHumanHand.size() / 2)) cout << endl;
	}
	cout << endl;
}

/* *********************************************************************
Function Name: DisplayMenu
Purpose: Virtual functon: to display the options menu before each Human turn
Parameters: vector of pointers of eligibleTrains, engine tile
Return Value: a string that denotes what option human player selected
Algorithm:
		1) user input
		2) input validation
		3) print statements
Assistance Received: none
********************************************************************* */

string Human::DisplayMenu(vector<Train*> a_EligibleTrains, Tile a_Engine) {
	string userInput;
	cout << "\n >> Human's Turn" << endl;
	cout << "--------------------" << endl;
	cout << "Please enter 'S' to save the game." << endl;
	cout << "Please enter 'Q' to quit the game. " << endl;
	cout << "Please enter 'M' to continue making moves. " << endl;
	cout << "Please enter 'H' for help." << endl;
	cin >> userInput;
	transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

	while (userInput != "H" && userInput != "M" && userInput != "S" && userInput != "Q") {
		cout << "Please enter 'H', 'M', 'S', or 'Q'." << endl;
		cin >> userInput;
		transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
	}

	if (userInput == "H") {
		Player::HelpHuman(a_EligibleTrains, mHumanHand, a_Engine);
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
Purpose: Virtual function, to find Humans eligible trains in the case where 
		 there is no orphan train
Parameters: htrain marker, ctrain marker, human, computer and mexican train by reference
Return Value: vector of pointers of eligible train for human
Algorithm:
		1) check if computer train has marker
		2) if yes add that to the eligible train vector
		3) Otherwise add htrain and mtrain references to the eligible trains vector
		4) return the vector
Assistance Received: none
********************************************************************* */

vector<Train *> Human::FindEligibleTrains(bool a_HTrainMarker, bool a_CTrainMarker, Train& a_Htrain, Train& a_Ctrain, Train& a_Mtrain) {
	
	vector<Train *> eligTrains = { &a_Mtrain, &a_Htrain };

	if (a_CTrainMarker) {
		eligTrains.push_back(&a_Ctrain);
	}

	return eligTrains;
}

/* *********************************************************************
Function Name:CheckPlayableTile
Purpose: Virtual function to check if human player has any playable tiles 
		 on hand, to play on its eligible trains
Parameters: vector of pointers of eligibletrains, engine tile
Return Value: true if human has playable tile else false
Algorithm:
		1) nested loop
		2) loop through all the eligible trains for human
		3) for each train, loop through the humanHand, and check if any tile
			in human hand is playable in the eligible train
		4) if one playable tile found, return true, and do not loop further

Assistance Received: none
********************************************************************* */

bool Human::CheckPlayableTile(vector<Train*> a_EligibleTrains, Tile a_Engine) {

	for (int i = 0; i < a_EligibleTrains.size(); i++) {
		for (int j = 0; j < mHumanHand.size(); j++) {

			Tile playableTile = Player::ValidateTile(mHumanHand[j], a_EligibleTrains[i]->GetTrainLastTile(a_Engine));

			//if the human player has atleast one tile on hand to play on one of the eligible trains, return true
			if(playableTile.GetTileLeft()!=-1)return true;
		}
	}

	cout << "You do not have any playable tile for the turn. Therefore, draw tile from boneyard." << endl;

	return false;

}

/* *********************************************************************
Function Name: DrawTile
Purpose: virtual function: to let human draw tile from boneyard, and add it
		 to human hand, whch will be played immediatly if the tile is playable
Parameters: boneyard by reference
Return Value: map of the drawn tile, which has the tile index and tile object
Algorithm:
		1) Take user input, validate the input, keep asking for input if input invalid
		2) store the first tile of boneyard as drawnTile in a tile object
		3) erase the first element of boneyard
		4) add the drawn tile to player's hand
		5) return the map of the drawn tile index in human hand, which is the last element,
			and the tile object
Assistance Received: none
********************************************************************* */

map<int, Tile> Human::DrawTile(vector<Tile>& a_Boneyard) {
	string userInput="";
	
	while (userInput != "B") {
		cout << "Please press 'B' to draw tile from boneyard." << endl;
		cin >> userInput;
		transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);
	}
	
	Tile drawnTile = a_Boneyard[0];
	a_Boneyard.erase(a_Boneyard.begin());

	//push the tile into humanhand which will be played immediately if possible
	mHumanHand.push_back(drawnTile);

	cout << "Drawn Tile : " << drawnTile.PrintTile() << endl;

	//a map of drawn tile and its index
	map<int, Tile> tileIndexMap;
	tileIndexMap.insert(pair<int, Tile>(mHumanHand.size()-1, drawnTile));

	return tileIndexMap;
}

/* *********************************************************************
Function Name: AddMarker
Purpose: Virtual function to add marker to human train if the drawn tile 
		 could not be played
Parameters: drawntile, vector of eligtrain pointers, engine, ctrain and htrain
			by reference
Return Value: true of need to add marker, false otherwise
Algorithm:
		1) loops through the eligible trains vectors and checks if the drawn	
			tile can be played in any of the trains
		2) if yes, returns false immediately
		3) If tile was not valid for any of the eligible trains, adds marker
			to human train, sets the explanation to display on screen that human
			could not play the turn
		4) If it was humans turn again, makes sure that its updated

Assistance Received: none
********************************************************************* */

bool Human::AddMarker(Tile a_drawnTile, std::vector<Train*> a_EligibleTrains, Tile a_Engine, Train& a_CTrain, Train& a_Htrain) {
	
	for (int i = 0; i < a_EligibleTrains.size(); i++) {

		Tile isValidTile = Player::ValidateTile(a_drawnTile, a_EligibleTrains[i]->GetTrainLastTile(a_Engine));

		//if the tile fits on any of the eligible train return false immediately
		if (isValidTile.GetTileLeft() != -1) {
			Player::SetExplanation("");
			cout << "Drawn Tile is playable. ";
			return false;
		}
	}
	//if human could not play a tile after playing an orphan tile, sets the hasToPlayOD variable to true so that human player
	//is forced to play on the OD train in next turn
	mHasToPlayOD = true;
	a_Htrain.UpdateTrainMarker(true);
	Player::SetExplanation("You could not play any tile because the tile drawn " + a_drawnTile.PrintTile() + " was not playable.");
	mplayedDblCount = 0; // making sure, its not human player's turn again, if it was
	return true;
}

/* *********************************************************************
Function Name: PickAtrain
Purpose: Virtual function to allow user to pick a train to place tile on 
		 from their eligigble trains
Parameters: vector of Eligible trains pointer, engine tile
Return Value: Picked train pointer
Algorithm:
		1) take user input and validate the input
		2) check if the train picked by the user is eligible in the turn
		3) If not eligible ask user to pick another train
		4) If eligible return the pointer of the picked train

Assistance Received: none
********************************************************************* */

Train* Human::PickAtrain(vector<Train *> a_EligibleTrains, Tile a_Engine) {
	
	string train;
	bool pickedEligTrain = false;
	
	int pickedtrainIndex = -1;
	
	cout << "Please pick a trian you want to place the tile on." << endl;
	while (pickedEligTrain == false) {
		
		cin >> train;
		transform(train.begin(), train.end(), train.begin(), ::toupper);
		
		if (train == "M") {
			//isGoodTrain returns the index of the train picked if it was eligible otherwise returns -1
			pickedtrainIndex = isGoodTrain(a_EligibleTrains, a_Engine, "M-Train");
			if (pickedtrainIndex > -1)
				return a_EligibleTrains[pickedtrainIndex];
		}
		else if(train == "H") {
			pickedtrainIndex = isGoodTrain(a_EligibleTrains, a_Engine, "H-Train");
			if (pickedtrainIndex > -1)
				return a_EligibleTrains[pickedtrainIndex];
		}
		else if(train == "C") {
			pickedtrainIndex = isGoodTrain(a_EligibleTrains, a_Engine, "C-Train");
			if (pickedtrainIndex > -1)
				return a_EligibleTrains[pickedtrainIndex];
		}
		else {
			cout << "No such train exists. Please enter 'H', 'M', or 'C'" << endl;
		}

		if (pickedEligTrain == false) {
			cout << "Please pick a train again." << endl;
		}
	}
	
	return a_EligibleTrains[0];
}

/* *********************************************************************
Function Name:PickATile
Purpose: Virtual function to allow user to pick a tile to place on the
		 picked train
Parameters: pointer of the picked train, engine tile
Return Value: a map of the index of picked tile and the tile object
Algorithm:
		1) take user input between 0 and size of humanhand - 1
		2) validate input, try parsing to int
		3) return the map of picked tile index in humanHand, and the
			tile object

Assistance Received: none
********************************************************************* */

map<int, Tile> Human::PickATile(Train* a_PickedTrain, Tile a_Engine) {

	int tileIndex = mHumanHand.size() + 1; // for the while loop condition
	string userInput;
	while (tileIndex >= mHumanHand.size()) {

		cout << "Please pick from your tiles in hand." << endl;
		cout << "Enter the number correspnding the tile to add the tile to the "<<
			a_PickedTrain->GetTrainName() <<" train." << endl;

		cin >> userInput;

		try {
			tileIndex = std::stoi(userInput);
		}
		catch(exception e){
			cout << "---Please enter an integer value between 0 and " << (mHumanHand.size()-1) << "---" << endl;
		}
	}

	Tile pickedTile = mHumanHand[tileIndex];

	std::map<int, Tile> TileIndexMap;
	TileIndexMap.insert(pair<int, Tile>(tileIndex, pickedTile));

	Player::SetExplanation("");
	return TileIndexMap;

}

/* *********************************************************************
Function Name: RemoveTileFromHand
Purpose: Virtual function to delete the played tile from user's hand
Parameters: picked tile index, played train, played tile object
Return Value: none
Algorithm:
		1) erase the element of the given index from humanhand
		2) call updatePlayerInfo function which updates the state of
			the player after playing a tile in a turn

Assistance Received: none
********************************************************************* */

void Human::RemoveTileFromHand(int a_index, Train* a_PlayedTrain, Tile a_PlayedTile) {
	mHumanHand.erase(mHumanHand.begin() + a_index);
	UpdatePlayerInfo(a_PlayedTrain, a_PlayedTile);
}

/* *********************************************************************
Function Name: UpdatePlayerInfo
Purpose: to update players state after playing a tile in a turn
Parameters: played train pointer, played tile
Return Value: none
Algorithm:
		1) if human played on its own train, update train marker to be false
			i.e. remove marker from human train if there was one
		2) if there was a message being displayed to the human previously
			after playing a tile, set that to empty
		3) Check if the played tile was double, is yes increase playedDblCount
			by one and set HasToPlayOD variable to false, since the player
			does not have to play the double tile immediately after
		4) If played tile was not double set the mPlayedDbl count back to 0,
			set HasToPlayOD to truw, which denotes that human has to play the 
			orphan double train in next turn

Assistance Received: none
********************************************************************* */

void Human::UpdatePlayerInfo(Train* a_PlayedTrain, Tile a_PlayedTile) {
	if (a_PlayedTrain->GetTrainName() == "H-Train") {
		a_PlayedTrain->UpdateTrainMarker(false);
		Player::SetExplanation("");
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
Purpose: Virtual function that denotes if the user can play again in the
		 same turn
Parameters:none
Return Value: true if can play again, false otherwise
Algorithm:
		1) If human had played a double tile either once or twice, the
		player can play again
		2) If double tile was not played cannot play again

Assistance Received: none
********************************************************************* */

bool Human::CanPlayAgain() {
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
		1) if humanhand size is 0 returns true otherwise false

Assistance Received: none
********************************************************************* */

bool Human::PlayerHandEmpty() {
	if (mHumanHand.size() == 0) {
		return true;
	}
	return false;
}

/* *********************************************************************
Function Name: isGoodTrain
Purpose: to check if the given train is eligible in the turn and if the 
		human player has playable tile for the train
Parameters: vector of eligTrains pointer, engine tile, picked train name
Return Value: index of the picked train or -1
Algorithm:
		1) loop through the eligtrains vector
		2) if the eligibletrain's name is same as picked train name check
			if user has playable tile for the train
			3) If user has no playable tile for train, print message to user
			and return -1
		4) if the picked train is not one of the eligible trains, print message
			to user and return -1
		5) If picked train is eligible and has playable tile for the train
			return the trains index from the eligTrains vector

Assistance Received: none
********************************************************************* */

int Human::isGoodTrain(vector<Train*> a_EligibleTrains, Tile a_Engine, string a_TrainName) {
	for (int i = 0; i < a_EligibleTrains.size(); i++) {
		if (a_EligibleTrains[i]->GetTrainName() == a_TrainName) {
			if (Player::HasPlayableTile(*a_EligibleTrains[i], mHumanHand, a_Engine)) {
				return i;
			}
			else {
				cout << a_TrainName << " is valid, but you do not have any matching tile for the train." << endl;
				return -1;
			}			
		}
	}

	cout << a_TrainName << " is not eligible in this turn." << endl;
	return -1; // the picked train was not eligible
}