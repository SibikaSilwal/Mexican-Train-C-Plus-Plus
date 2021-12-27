/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#include "Player.h"
#include<iostream>
#include<iomanip>
#include<vector>
#include<stdlib.h>

using namespace std;

/* *********************************************************************
Function Name: PLayer
Purpose: to consturct player class object
Parameters: none
Return Value: none
Algorithm:none
Assistance Received: none
********************************************************************* */
Player::Player() {
	mExplainTurn = "";
}

/* *********************************************************************
Function Name: GetPlayerScore
Purpose: Calculates the players score which is a sum of the tile pips in 
			players hand
Parameters: playerHand, the tiles in player's hand
Return Value: sum of the tile pips which is an integer
Algorithm:
		1) returns the sum of left and right pips of all the tiles in
			players hand

Assistance Received: none
********************************************************************* */

int Player::GetPlayerScore(vector<Tile> a_PlayerHand) {
	int score = 0;
	for (int i = 0; i < a_PlayerHand.size(); i++) {
		score = score + a_PlayerHand[i].GetTileLeft() + a_PlayerHand[i].GetTileRight();
	}
	return score;
}

/* *********************************************************************
Function Name: GetOrpDblTrain
Purpose: Return a list of orphan double trains
Parameters: vectors of pointers of train objects
Return Value: vector of pointers of orphan double trains
Algorithm:
		1) loops through the vector of the trains, adds the points of
			orphan double trains to a temporary vector, and returns the
			vector at the end
Assistance Received: none
********************************************************************* */

vector<Train*> Player::GetOrpDblTrain(vector<Train*> a_trains) {
	vector<Train*> OrpDblTrains;
	for (int i = 0; i < a_trains.size(); i++) {
		if (a_trains[i]->IsOrphDoubleTrain()) {
			OrpDblTrains.push_back(a_trains[i]);
		}
	}
	return OrpDblTrains;
}

/* *********************************************************************
Function Name:
Purpose:
Parameters:
Return Value:
Algorithm:
		1)

Assistance Received: none
********************************************************************* */

vector<Train *> Player::FindEligibleTrains(bool a_HTrainMarker, bool a_CTrainMarker, Train& a_Htrain, Train& a_Ctrain, Train& a_Mtrain) {
	
	std::vector<std::string> eligibleTrains = { "M" };
	vector<Train *> eligTrain = { &a_Mtrain };
	return eligTrain;
};

//virtual function, that does nothing in player class
map<int, Tile> Player::DrawTile(vector<Tile>& a_Boneyard) {
	map<int, Tile> defaultmap;
	defaultmap.insert(pair<int, Tile>(-1, Tile(10, 10)));
	return defaultmap;
}

/* *********************************************************************
Function Name: DrawMove
Purpose: Move steps to follow when boneyard tile needs to be drawn
Parameters:vector of pointers of a_EligibleTrains, engine tile, boneyard reference, c-train reference, h-train reference
Return Value: none
Algorithm:
		1) Check if boneyard is empty, if yes add marker on players train and return
		2) If boneyard is not empty Draw tile from Boneyard
		3) Check if the drawn tile was a playable tile for the player in their eligible trains.
			- If yes, ask player to pick a train to add the tile to
			- validate the tile for the picked train
			- add tile to the train (if tile valid), else ask to pick another train again
		4) If drawn tile was not playable, add tile to players hand, and add marker to player's train
		5) return

Assistance Received: none
********************************************************************* */

void Player::DrawMove(std::vector<Train*> a_EligibleTrains, Tile a_Engine, vector<Tile>& a_Boneyard, Train& a_ctrain, Train& a_htrain) {

	if (a_Boneyard.empty()) {
		AddMarker(Tile(-5, -5), a_EligibleTrains, a_Engine, a_ctrain, a_htrain);
		SetExplanation("Boneyard is empty. Player passed its turn");
		system("cls");
		return;
	}

	map<int, Tile> pickedTileMap = DrawTile(a_Boneyard);
	int tileIndex = pickedTileMap.begin()->first;
	Tile drawnTile = pickedTileMap.begin()->second;


	//check if the drawntile is playable for the eligible trains
	bool drawnTileInValid = AddMarker(drawnTile, a_EligibleTrains, a_Engine, a_ctrain, a_htrain);

	//if AddMarker == true, drawn tile was not valid therefore no play.
	if (drawnTileInValid) {
		system("CLS");
		return;
	}

	if (!drawnTileInValid) {
		
		//choose train, validate tile for the train, add tile to the train
		Train* pickedTrain = PickAtrain(a_EligibleTrains, a_Engine);

		Tile validTile = ValidateTile(drawnTile, pickedTrain->GetTrainLastTile(a_Engine));

		if (validTile.GetTileLeft() != -1) {
			//if the validTile is a double tile, check if player can play double at the moment
			if (validTile.IsDoubleTile()) {
				if (!CanPlayDoubleTile(a_EligibleTrains, pickedTileMap, *pickedTrain, GetPlayerHand(), a_Engine)) {
					return;
				}
			}
			system("CLS");
			(*pickedTrain).AddTileOnTrain(validTile);
			RemoveTileFromHand(tileIndex, pickedTrain, validTile);
			cout << "Drawn Tile: " << drawnTile.PrintTile() << endl;
		}

		return;

	}
}

//virtual function to make the players pick a train, does not do anything from player class
Train* Player::PickAtrain(vector<Train *> a_EligibleTrains, Tile a_Engine) {
	return a_EligibleTrains[0];
};

//vritual function to make players pick a tile, does not do anything from players class
map<int, Tile> Player::PickATile(Train* a_PickedTrain, Tile a_Engine) {
	map<int, Tile> defaultmap;
	defaultmap.insert(pair<int, Tile>(-1, Tile(10, 10)));
	return defaultmap;
}

/* *********************************************************************
Function Name: ValidateTile
Purpose: to validate the picked tile by user before adding it to the train
Parameters: picked tile, last tile of the train where the tile is being added
Return Value: Tile object
Algorithm:
		1) Checks the picked tile against the lastTile passed as a parameter
		2) if the picked tile left pips is equal to lastTile's left pip, 
			return the tile as is, as a valid tile
		3) if the picked tile left pips is equal to lasttile's right pip,
			switches the left and right pip value for the tile, and returns
			the tile as a valid tile
		4) if the picked tile pips do not match left or right pips of the last 
			tile returns a default tile Tile(-1, -1) which denotes that the picked
			tile was not valid

Assistance Received: none
********************************************************************* */
Tile Player::ValidateTile(Tile a_PlayingTile, Tile a_LastTile) {
	Tile defaultTile(-1,-1);
	int lastTilePips = a_LastTile.GetTileRight();

	if (a_PlayingTile.GetTileLeft() == lastTilePips) 
	{
		return a_PlayingTile;
	}
	else if (a_PlayingTile.GetTileRight() == lastTilePips) {

		int tileLeft = a_PlayingTile.GetTileLeft();
		int tileRight = a_PlayingTile.GetTileRight();
		a_PlayingTile.SetTileLeft(tileRight);
		a_PlayingTile.SetTileRight(tileLeft);

		return a_PlayingTile;
	}
	else {
		return defaultTile;
	}


	return defaultTile;
	
}

/* *********************************************************************
Function Name:MakeMove
Purpose: to let the player make its move
Parameters: engine, h-train, c-train, m-train, boneyard, gameState all passed by reference
Return Value:none
Algorithm:
		1) get eligible trains
		2) check if player has playable tiles on hand
		3) if not draw tile from boneyard and playTile immediately
		4) if yes, let player choose a train 
		5) If user does not have a playable tile on hand for the train, notify user and let user choose train again
		6) let user choose a tile and add it to the train
		7) Remove the played tile from player's hand

Assistance Received: none
********************************************************************* */
void Player::MakeMove(Tile a_engine, Train& a_Htrain, Train& a_Ctrain, Train& a_Mtrain, vector<Tile>& a_Boneyard, string& a_gameState) {
	
	


	// 1. get eligible trains
	vector<Train*> trains = { &a_Mtrain, &a_Htrain, &a_Ctrain };
	vector<Train*> eligTrains;
	if ((GetOrpDblTrain(trains).size()) > 0 && (HasToPlayOD() == true)) {
		eligTrains = GetOrpDblTrain(trains);
	}
	else {
		eligTrains = FindEligibleTrains(a_Htrain.TrainHasMarker(), a_Ctrain.TrainHasMarker(), a_Htrain, a_Ctrain, a_Mtrain);
	}

	a_gameState = DisplayMenu(eligTrains, a_engine);
	if (a_gameState == "save" || a_gameState == "quit") {
		return;
	}
	
	
	// 2. check if player has tiles or need to draw from boneyard
	bool hasPlayableTile = CheckPlayableTile(eligTrains, a_engine);

	if (!hasPlayableTile) {
		DrawMove(eligTrains, a_engine, a_Boneyard, a_Ctrain, a_Htrain);
		return;	
	}

	// 3. If no drawing required
	Train* pickedTrain = PickAtrain(eligTrains, a_engine);

	map<int, Tile> pickedTileMap = PickATile(pickedTrain, a_engine);

	Tile validTile = ValidateTile(pickedTileMap.begin()->second, pickedTrain->GetTrainLastTile(a_engine));

	//keep asking for tile until a valid tile is chosen
	while(validTile.GetTileLeft() == -1) {
		pickedTileMap = PickATile(pickedTrain, a_engine);
		validTile = ValidateTile(pickedTileMap.begin()->second, pickedTrain->GetTrainLastTile(a_engine));
		cout << "The tile placement does not follow the rule. Please select another tile." << endl;
	}


	//if the validTile is a double tile, check if player can play double at the moment
	if (validTile.IsDoubleTile()) {
		if (!CanPlayDoubleTile(eligTrains, pickedTileMap, *pickedTrain, GetPlayerHand(), a_engine)) {
			//keep asking for tile until a valid tile is chosen
			while (validTile.GetTileLeft() == -1) {
				pickedTileMap = PickATile(pickedTrain, a_engine);
				validTile = ValidateTile(pickedTileMap.begin()->second, pickedTrain->GetTrainLastTile(a_engine));
				cout << "The tile placement does not follow the rule. Please select another tile." << endl;
			}
		}
	}
	system("CLS");
	RemoveTileFromHand(pickedTileMap.begin()->first, pickedTrain, validTile);
	(*pickedTrain).AddTileOnTrain(validTile); // add picked tile on the picked train

}

/* *********************************************************************
Function Name: CanPlayDoubleTile
Purpose: to check if the player can play double tile in the turn
Parameters: a_EligibleTrains, a_PickedTileMap, a_PlayerHand, a_Engine
Return Value: true or false
Algorithm:
		1) if player is playng double for the first time in the turn return true
		2) if player is playing double for the second time in its turn, check
			- get the double tile and the tile index picked by the player
			- remove the picked tile from the copy of players hand
			- add the tile to the copy of picked train
			- make a copy of users eligtrains with the updated trains
			- check if user can play another tile in one of these updated eligtrains 
				from its updated playerHand
			- if can play return true
			- else return false
		3) if none of the conditions above match, return false


Assistance Received: none
********************************************************************* */
bool Player::CanPlayDoubleTile(vector<Train*> a_EligibleTrains, map<int, Tile> a_PickedTileMap, Train PickedTrain, vector<Tile> a_PlayerHand, Tile a_Engine) {
	if (GetPlayedDoubleCount() == 0) {
		return true;
	}
	int dblTileIndex = a_PickedTileMap.begin()->first;
	Tile dblTile = a_PickedTileMap.begin()->second;
	string trainName = PickedTrain.GetTrainName();
	bool canPlayDouble = false;
	vector<Train> EligTrainCopy;
	if (GetPlayedDoubleCount() == 1) {
		a_PlayerHand.erase(a_PlayerHand.begin() + dblTileIndex);
		PickedTrain.AddTileOnTrain(dblTile);
		for (int i = 0; i < a_EligibleTrains.size(); i++) {
			if (a_EligibleTrains[i]->GetTrainName() == trainName) {
				EligTrainCopy.push_back(PickedTrain);
			}
			else {
				EligTrainCopy.push_back(*a_EligibleTrains[i]);
			}
		}
		for (int i = 0; i < EligTrainCopy.size(); i++) {
			if (HasPlayableTile(EligTrainCopy[i], a_PlayerHand, a_Engine))
				return true;
		}
	}
	cout << "Cannot play a double again" << endl;
	return false;
}

/** Winning Strategies **/

/* *********************************************************************
Function Name: FindLargestTileIndex
Purpose: to find the largest tile that can be played in the turn
Parameters: a_endTilePips of the picked train, playerHand
Return Value: a map<int, Tile> of tile index in player hand, and the tile object
Algorithm:
		1) loop through the player's hand and return the map of
			largest valid tile index and the tile

Assistance Received: none
********************************************************************* */

map<int, Tile> Player::FindLargestTileIndex(int a_endTilePips, std::vector<Tile> a_PlayerHand) {
	int largestpip=-1;
	int largestTileIndex=0;
	map<int, Tile> TileIndexMap;
	Tile lastTile(10, a_endTilePips);
	Tile ValidTile(-1, -1);

	for (int i = 0; i < a_PlayerHand.size(); i++) {
		ValidTile = ValidateTile(a_PlayerHand[i], lastTile);
		if ( ValidTile.GetTileLeft() != -1) {
			if (ValidTile.GetTileRight() > largestpip) {
				largestpip = ValidTile.GetTileRight();
				largestTileIndex = i;
			}
		}
	}
	TileIndexMap.insert(pair<int, Tile>(largestTileIndex, a_PlayerHand[largestTileIndex]));
	return TileIndexMap;
}

/* *********************************************************************
Function Name: FindDoubelTile
Purpose: find a double tile that can be played in the turn
Parameters: eligtrain, playerhand, engine tile
Return Value: a map<int, Tile> of the double tile index in player hand, and the tile object
Algorithm:
		1) loop through the player hand
		2) if a valid double tile found, return the map of the tile's index and the tile object
		3) else return a defalut map with -1 index and tile(-1,-1)

Assistance Received: none
********************************************************************* */

map<int, Tile> Player::FindDoubelTile(Train a_eligTrain, std::vector<Tile> a_PlayerHand, Tile a_Engine) {
	map<int, Tile> TileIndexMap;
	Tile ValidTile(-1, -1);
	
	for (int i = 0; i < a_PlayerHand.size(); i++) {
		ValidTile = ValidateTile(a_PlayerHand[i], a_eligTrain.GetTrainLastTile(a_Engine));
		if (ValidTile.GetTileLeft() != -1) {
			if (ValidTile.IsDoubleTile()) {
				TileIndexMap.insert(pair<int, Tile>(i, a_PlayerHand[i]));
				return TileIndexMap;
			}
		}
	}	
	TileIndexMap.insert(pair<int, Tile>(-1, Tile(-1,-1))); //matching double tile not found
	return TileIndexMap;
}

/* *********************************************************************
Function Name: MakeOrphanTrain
Purpose: check if the player can create an orphan train in its turn
Parameters:vector of pointers of eligTrains, playerhand by value, engine tile
Return Value:
Algorithm:
		1) if the number of eligible trains <= 1 , cannot make orphan train
		2) else, loop through the eligible trains, and find a playable double tile on each train
		3) if tile found,erase the tile from the players hand
		4) check if the player has any playable tiles in other eligtrains, except for the one where it would place
			the double tile
		5) if eligtrains to place second tile found, the player can make an orphan train
		6) return the possible orphan train information in a map.

Assistance Received: none
********************************************************************* */

map<string, string> Player::MakeOrphanTrain(vector<Train*> a_EligibleTrains, vector<Tile> a_PlayerHand, Tile a_Engine) {
	map<string, string> MakeOrphan;
	MakeOrphan["possible"] = "no";

	//not possible to make an orphan train if the # of eligible trains are only one
	if (a_EligibleTrains.size() <= 1) return MakeOrphan;

	for (int i = 0; i < a_EligibleTrains.size(); i++) {
		map<int, Tile> doubleTile = FindDoubelTile(*a_EligibleTrains[i], a_PlayerHand, a_Engine);
		if (doubleTile.begin()->first != -1) {
			a_PlayerHand.erase(a_PlayerHand.begin() + doubleTile.begin()->first);
			for (int j = 0; j < a_EligibleTrains.size(); j++) {
				if (j != i) {
					if (HasPlayableTile(*a_EligibleTrains[j], a_PlayerHand, a_Engine)) {
						MakeOrphan.empty();
						MakeOrphan["possible"] = "yes";
						MakeOrphan["trainName"] = a_EligibleTrains[i]->GetTrainName();
						MakeOrphan["tile"] = doubleTile.begin()->second.PrintTile();
						MakeOrphan["secondTrain"] = a_EligibleTrains[j]->GetTrainName();
						return MakeOrphan;
					}					
				}
			}
		}
	}
	return MakeOrphan; // if here, can't make orphan
}

/* *********************************************************************
Function Name: HasPlayableTile
Purpose:to check if the player has a playable tile for the picked train
Parameters:a_pickedTrain, playerhand, engine tile
Return Value: true ot false
Algorithm:
		1) loop through player hand, return true if a valid tile found for the
			picked train
		2) else return false

Assistance Received: none
********************************************************************* */

bool Player::HasPlayableTile(Train a_pickedTrain, std::vector<Tile> a_PlayerHand, Tile a_Engine) {

	for (int j = 0; j < a_PlayerHand.size(); j++) {

		Tile playableTile = Player::ValidateTile(a_PlayerHand[j], a_pickedTrain.GetTrainLastTile(a_Engine));

		//if the player has atleast one tile on hand to play on the eligible trains, return true
		if (playableTile.GetTileLeft() != -1)return true;
	}
	return false;
}

/* *********************************************************************
Function Name: HelpHuman
Purpose: to help human to make winning moves in its turn
Parameters: eligibleTrains, HumanHand, Engine tile
Return Value: none
Algorithm:
		1) create bool variables for all the trains human can play and has playable tiles for
			among the 3 trains
		2) Play 2 doubles and a non-double whenever possible
		2) check if human can make orphan train, if yes, give the suggestion for tile and train
		3) check if opponents train is playable, if yes, try to play double, otherwise play largest tile
		4) if it was an orphan train created by opponent player, notify user that it is the only playable train
		5) If orphan trains were made by the human player in previous turn, suggest not to break them, if possible
		6) if cannot make orphan train, try to play double tile on same trains
		7) if can't play double tile, play largest tile among the eligible trains
		8) if mexican train was not started, start mexican train if possible

Assistance Received: none
********************************************************************* */

void Player::HelpHuman(vector<Train*> a_EligibleTrains, vector<Tile> a_HumanHand, Tile a_Engine) {
	cout << left << setw(10) << " ";
	
	int hTrainIndex = -1; int mTrainIndex = -1; int cTrainIndex = -1;
	bool canPlayHTrain = false; bool canPlayMTrain = false; bool canPlayCTrain = false;
	int playableTrainCount = 0;

	for (int i = 0; i < a_EligibleTrains.size(); i++) {
		if (a_EligibleTrains[i]->GetTrainName() == "H-Train") {
			hTrainIndex = i;
			if (Player::HasPlayableTile(*a_EligibleTrains[hTrainIndex], a_HumanHand, a_Engine)) {
				canPlayHTrain = true;
				playableTrainCount++;
			}
		}
		if (a_EligibleTrains[i]->GetTrainName() == "M-Train") {
			mTrainIndex = i;
			if (Player::HasPlayableTile(*a_EligibleTrains[mTrainIndex], a_HumanHand, a_Engine)) {
				canPlayMTrain = true;
				playableTrainCount++;
			}
		}
		if (a_EligibleTrains[i]->GetTrainName() == "C-Train") {
			cTrainIndex = i;
			if (Player::HasPlayableTile(*a_EligibleTrains[cTrainIndex], a_HumanHand, a_Engine)) {
				canPlayCTrain = true;
				playableTrainCount++;
			}
		}
	}

	//Pick a train that can make an orphan train if possible
	map<string, string> makeOrphan = Player::MakeOrphanTrain(a_EligibleTrains, a_HumanHand, a_Engine);

	if (makeOrphan.find("possible")->second == "yes") {
		PrintHumanHelp(makeOrphan.find("tile")->second, makeOrphan.find("trainName")->second,
			" is a double tile that can make an orphan train.");
		return;
	}
	
	//Play on Computer's train when possible
	if (canPlayCTrain) {
		if (a_EligibleTrains[cTrainIndex]->IsOrphDoubleTrain() && playableTrainCount == 1) {
			Tile largestTile = FindLargestTileIndex(a_EligibleTrains[cTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight(), a_HumanHand).begin()->second;
			PrintHumanHelp(largestTile.PrintTile(), "Computer Train", " is the largest tile in your hand and computer's train is an orphan train.");
			return;
		}
		map<int, Tile> doubleTileMap = FindDoubelTile(*a_EligibleTrains[cTrainIndex], a_HumanHand, a_Engine);

		//if playable double tile is found, play double tile, else play the largest pips tile
		if (doubleTileMap.begin()->first != -1) {
			Tile doubleTile = doubleTileMap.begin()->second;
			PrintHumanHelp(doubleTile.PrintTile(), "Computer Train", " is a double tile in your hand and computer's train has a marker.");
		}
		else {
			Tile largestTile = FindLargestTileIndex(a_EligibleTrains[cTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight(), a_HumanHand).begin()->second;
			PrintHumanHelp(largestTile.PrintTile(), "Computer Train", " is the largest tile in your hand and computer's train has a marker.");
		}
		return;
	}
	

	//m-train second priority if it is not started already
	if (canPlayMTrain) {
		if (a_EligibleTrains[mTrainIndex]->GetTrain().size() == 0) {
			Tile largestTile = FindLargestTileIndex(a_EligibleTrains[mTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight(), a_HumanHand).begin()->second;
			PrintHumanHelp(largestTile.PrintTile(), "Mexican Train", "it is not started yet, and starting the Mexican Train as soon as possible will be benifitial in future.");
			return;
		}	
	}

	//try not to break the orphan double train
	if (playableTrainCount > 1) {
		if (canPlayHTrain && a_EligibleTrains[hTrainIndex]->IsOrphDoubleTrain()) {
			if (canPlayMTrain) {
				Tile largestTile = FindLargestTileIndex(a_EligibleTrains[mTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight(), a_HumanHand).begin()->second;
				PrintHumanHelp(largestTile.PrintTile(), "Mexican Train",
					" is the largest tile on your hand.\nI suggest you DO NOT play on Your Train because it is a double train you created.");
			}
			if (canPlayCTrain) {
				Tile largestTile = FindLargestTileIndex(a_EligibleTrains[cTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight(), a_HumanHand).begin()->second;
				PrintHumanHelp(largestTile.PrintTile(), "Computer Train",
					" is the largest tile on your hand.\nI suggest you DO NOT play on Your Train because it is a double train you created.");
			}
			return;
		}
		if (canPlayMTrain && a_EligibleTrains[mTrainIndex]->IsOrphDoubleTrain()) {
			if (canPlayCTrain) {
				Tile largestTile = FindLargestTileIndex(a_EligibleTrains[cTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight(), a_HumanHand).begin()->second;
				PrintHumanHelp(largestTile.PrintTile(), "Computer Train",
					" is the largest tile on your hand. I suggest you DO NOT play on Mexican Train because it is a double train you created.");
			}
			if (canPlayHTrain) {
				Tile largestTile = FindLargestTileIndex(a_EligibleTrains[hTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight(), a_HumanHand).begin()->second;
				PrintHumanHelp(largestTile.PrintTile(), "Human Train",
					" is the largest tile on your hand. I suggest you DO NOT play on Mexican Train because it is a double train you created.");
			}
			return;
		}
		if (canPlayCTrain && a_EligibleTrains[cTrainIndex]->IsOrphDoubleTrain()) {
			if (canPlayMTrain) {
				Tile largestTile = FindLargestTileIndex(a_EligibleTrains[mTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight(), a_HumanHand).begin()->second;
				PrintHumanHelp(largestTile.PrintTile(), "Mexican Train",
					" is the largest tile on your hand. I suggest you DO NOT play on Computer Train because it is a double train you created.");

			}
			if (canPlayHTrain) {
				Tile largestTile = FindLargestTileIndex(a_EligibleTrains[hTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight(), a_HumanHand).begin()->second;
				PrintHumanHelp(largestTile.PrintTile(), "Human Train",
					" is the largest tile on your hand. I suggest you DO NOT play on Computer Train because it is a double train you created.");

			}
			return;
		}
	}

	//if can play double tile, play double tile
	if (canPlayMTrain) {
		map<int, Tile> doubleTileMap = FindDoubelTile(*a_EligibleTrains[mTrainIndex], a_HumanHand, a_Engine);
		//if playable double tile is found, play double tile, else play the largest pips tile
		if (doubleTileMap.begin()->first != -1) {
			Tile doubleTile = doubleTileMap.begin()->second;
			PrintHumanHelp(doubleTile.PrintTile(), "Mexican Train", " is a double tile in your hand that can be played.");
			return;
		}

	}
	if (canPlayHTrain) {
		map<int, Tile> doubleTileMap = FindDoubelTile(*a_EligibleTrains[hTrainIndex], a_HumanHand, a_Engine);
		//if playable double tile is found, play double tile, else play the largest pips tile
		if (doubleTileMap.begin()->first != -1) {
			Tile doubleTile = doubleTileMap.begin()->second;
			PrintHumanHelp(doubleTile.PrintTile(), "your Train", " is a double tile in your hand that can be played.");
			return;
		}
	}
	

	//if can't make orphan train, choose between trains that can use larger pip tile
	if (canPlayMTrain && canPlayHTrain)
	{
		int mTrainPips = a_EligibleTrains[mTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight();
		int hTrainPips = a_EligibleTrains[hTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight();

		Tile MTile = Player::FindLargestTileIndex(mTrainPips, a_HumanHand).begin()->second;
		Tile HTile = Player::FindLargestTileIndex(hTrainPips, a_HumanHand).begin()->second;

		if ((MTile.GetTileLeft() + MTile.GetTileRight()) >= (HTile.GetTileLeft() + HTile.GetTileRight())) {
			PrintHumanHelp(MTile.PrintTile(), "Mexican Train"," is the largest tile on your hand you can play in this turn.");
		}
		else {
			PrintHumanHelp(HTile.PrintTile(), "your Train", " is the largest tile on your hand you can play in this turn.");
		}
		return;
	}

	//if can't compare tiles on mtrain and ctrain because of available tiles, prioritize mtrain then htrain
	if (canPlayMTrain) {
		int mTrainPips = a_EligibleTrains[mTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight();
		Tile MTile = Player::FindLargestTileIndex(mTrainPips, a_HumanHand).begin()->second;
		PrintHumanHelp(MTile.PrintTile(), "Mexican Train", " is the largest tile on your hand you can play in this turn.");
		return;
	}

	if (canPlayHTrain) {
		int hTrainPips = a_EligibleTrains[hTrainIndex]->GetTrainLastTile(a_Engine).GetTileRight();
		Tile HTile = Player::FindLargestTileIndex(hTrainPips, a_HumanHand).begin()->second;
		PrintHumanHelp(HTile.PrintTile(), " your Train", " is the largest tile on your hand you can play in this turn.");
		return;
	}
}

/* *********************************************************************
Function Name: PrintGameStrategy
Purpose: to print the computer's game strategy
Parameters: none
Return Value: none
Algorithm:none
Assistance Received: none
********************************************************************* */

void Player::PrintGameStrategy() {

	if (mExplainTurn != "") {
		cout << left << setw(10) << " ";
		cout << mExplainTurn << endl;
	}

}