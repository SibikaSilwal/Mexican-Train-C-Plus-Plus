/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#include "Round.h"
#include"Player.h"
#include"Game.h"
#include<iomanip>
#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<algorithm>
#include <fstream>
#include <sstream>

/* *********************************************************************
Function Name: Round
Purpose: To construct a Round Object
Parameters:none
Return Value: none
Algorithm:
		1) Initializes all the member variables of the class to their default values
Assistance Received: none
********************************************************************* */
Round::Round() {
	mRoundNumber = 1;
	mEngineIndex = 55;
	mHumanScore = 0;
	mComputerScore = 0;
	mGameState = "";
	mBoneYard = {};
	mTurnHuman = false;
	mTurnComputer = false;
	mHumanTrain.SetTrainName("H-Train");
	mMexicanTrain.SetTrainName("M-Train");
	mComputerTrain.SetTrainName("C-Train");
}

/* *********************************************************************
Function Name: GetEngineIndex
Purpose: To compute the engine tile index for the current round
Parameters:none
Return Value: Engine tile index computed
Algorithm:
		1) Uses the current round number to calculate the engine index
		2) If the round # is divisible by 10 the index is 0, which is
			the base case
		3) Otherwise, loops through 0 to 9, and returns the engine index
			by subtracting the previous engine index value.
Assistance Received: none
********************************************************************* */

int Round::GetEngineIndex() {

	if (mRoundNumber % 10 == 0) {
		mEngineIndex = 0;
		return mEngineIndex;
	}
	for (int i = 0; i <= 10; i++) {
		mEngineIndex = mEngineIndex - i;

		if (i == mRoundNumber % 10) {
			return mEngineIndex;
		}
	}
	return 0; //default, which should not happen
}

/* *********************************************************************
Function Name: PrintBoneYard
Purpose: To print the boneyard tiles to the console
Parameters:none
Return Value: none
Algorithm:
		1) Displaying the tiles in the mBoneyard vector
Assistance Received: none
********************************************************************* */

void Round::PrintBoneYard() {
	cout << "Boneyard Tiles: (" << mBoneYard.size() << ") -> ";
	
	for (int i = 0; i < mBoneYard.size(); i++) {
		cout << mBoneYard[i].GetTileLeft() << "-" << mBoneYard[i].GetTileRight() << "  ";
	}
	cout << endl;
}

/* *********************************************************************
Function Name: TossACoin
Purpose: To determine which player plays first my letting user call for
		 the coin toss
Parameters:none
Return Value: none
Algorithm:
		1) Generated a random value between 0 and 1
		2) Assiciated # 0 with head and # 1 with tail
		3) Asked for user input, if the input aligns with the number
		   generated, human turn set as true
		4) Let user know who plays next by printing the output
Assistance Received: none
********************************************************************* */

void Round::TossACoin() {

	int head = 0, tail = 1, humanCall;
	string humanChoice, headTail;

	//take user input
	cout << "Please choose between Head and Tail for coin toss." << endl;
	cout << "Press 'H' for head and 'T' for tail." << endl;
	cin >> humanChoice;
	transform(humanChoice.begin(), humanChoice.end(), humanChoice.begin(), ::toupper);

	//validate user input
	while (humanChoice != "H" && humanChoice != "T") {
		cout << "Sorry your entry was invalid. Please press 'H' or 'T'" << endl;
		cin >> humanChoice;

		transform(humanChoice.begin(), humanChoice.end(), humanChoice.begin(), ::toupper);
	
		humanCall = humanChoice == "H" ? head : tail;
	}

	humanCall = humanChoice == "H" ? head : tail;

	//generate random number between 0 and 1 for coin toss
	std::srand(time(0));
	int toss = rand() % 2;

	//compare human call with random # generated, if same human won the toss
	if (humanCall == toss) {
		cout << setw(10) << "Human won the toss. Human plays first !" << endl;
		mTurnHuman = true;
	}
	else {
		cout << setw(10) << "Human lost the toss. Computer plays first !" << endl;
		mTurnComputer = true;
	}

	system("pause");
}

/* *********************************************************************
Function Name: InitializeRound
Purpose: To start a new round in a game, reset all the tiles, and place
		 new engine for the round
Parameters: a game class object passed by reference
Return Value: none
Algorithm:
		1) Creates two players object and dynamically casts them to human
			and computer class objects. These are the two player objects that
			are used through out the round to play the round
		2) If it the round is 1, ask user if they want to start a new game
			or load an old game from file
		3) While starting a fesh round, place engine, shuffle deck, deal deck
			and toss a coin
		4) Let the player who won the toss play first
		5) Keep playing until the game ends by one of the possible reason
			-user quits, asks to save, player hand empty, boneyard empty and
			both players passed their turns.
		6) If loading a new game, call the assocaited functions and pass the
			player objects to be populated.
Assistance Received: none
********************************************************************* */

void Round::InitializeRound(Game* a_gameObject) {

	Tile engine(-5, -5);

	//create player objects
	Player* players[2];
	players[0] = new Human();
	players[1] = new Computer();
	
	//objects cast to human and computer object
	Human* humanPlayer = new Human();
	humanPlayer = dynamic_cast<Human*>(players[0]);

	Computer* computerPlayer = new Computer();
	computerPlayer = dynamic_cast<Computer*>(players[1]);
	
	string userInput="";

	// ask this only when the game is just started i.e. round # = 1
	if (mRoundNumber == 1) {
		cout << "Enter 'L' to load a saved game from a file or Enter 'C' to continue" << endl;

		//validate input
		while (userInput != "L" && userInput != "C") {
			cin >> userInput;
			transform(userInput.begin(), userInput.end(), userInput.begin(), ::toupper);

			//load game from file
			if (userInput == "L") {
				StartGameFromFile(*humanPlayer, *computerPlayer, *a_gameObject);
				engine = mDeck.PlaceEngine(GetEngineIndex());
			}
			//start new game
			else if (userInput == "C") {
				engine = mDeck.PlaceEngine(GetEngineIndex());
				mDeck.ShuffleDeck();
				mDeck.DealDeck(*humanPlayer, *computerPlayer, mBoneYard);
				TossACoin();
			}
			//ask for input again
			else {
				cout << "Please enter 'L' or 'C' " << endl;
			}
		}
	}
	//if round was not # 1, proceed with initializing round by shuffling and dealing decks
	else {
		engine = mDeck.PlaceEngine(GetEngineIndex());
		mDeck.ShuffleDeck();
		mDeck.DealDeck(*humanPlayer, *computerPlayer, mBoneYard);
		
		//lowest score player plays first
		if (a_gameObject->GetHumanScore() < a_gameObject->GetComputerScore()) mTurnHuman = true;
		if (a_gameObject->GetHumanScore() == a_gameObject->GetComputerScore()) TossACoin();
	}
	system("CLS");

	//print everything-> hands, trains, boneyard, engine, round #, socres to the console
	PrintScene(*humanPlayer, *computerPlayer, engine, *a_gameObject);

	int playerIndex = 1;

	//if human had won the toss human plays first
	if (mTurnHuman) playerIndex = 0; //if human wins the toss human plays first otherwise computer plays first

	//allow users to keep playing the round until the round or game ends for a reason
	while (!players[0]->PlayerHandEmpty() && !players[1]->PlayerHandEmpty()) {

		//current player makes its move
		players[playerIndex]->MakeMove(engine, mHumanTrain, mComputerTrain, mMexicanTrain, mBoneYard, mGameState);

		//after the move, if player wants to save the game, save the game
		if (mGameState == "save") {
			SaveGame(*humanPlayer, *computerPlayer, engine, playerIndex, *a_gameObject);
			cout << "Game Saved..." << endl;
			exit(0);
		}
		//if human wants to quit, quit the game, display the winner, kill the program
		if (mGameState == "quit") {
			int totalHumanScore = mHumanScore + a_gameObject->GetHumanScore();
			int totalComputerScore = mComputerScore + a_gameObject->GetComputerScore();
			cout << "Final scores are: \nHuman: " << totalHumanScore << " \nComputer: " << totalComputerScore << endl;

			if (totalHumanScore < totalComputerScore) cout << "\n>> Congratulations you won the game :) !!\n";
			else if(totalHumanScore == totalComputerScore) cout << "\n>> No body won the game. It's a tie between you and the computer :|\n";
			else cout << "\n>> You lost the game :( Computer won the game.\n" << endl;
			exit(0);
		}
		//print updated information
		PrintScene(*humanPlayer, *computerPlayer, engine, *a_gameObject);

		//print the game's strategy to the screen (computer strategy and message for human in some cases)
		players[playerIndex]->PrintGameStrategy();
		
		//if the same player can play again, dont change player
		if(players[playerIndex]->CanPlayAgain()) {
			playerIndex = playerIndex;
		}
		//otherwise switch between current and next player
		else {
			if (playerIndex == 0) 
				playerIndex = 1;
			else
				playerIndex = 0;
		}
		
		//if both players have marker and boneyard is empty round ends. Return
		if (mHumanTrain.TrainHasMarker() && mComputerTrain.TrainHasMarker() && mBoneYard.empty()) {
			cout << "Boneyard is empty and both the players passed their turns. Therefore, game ended!\n" << endl;
			break;
		}
	}

}


/* *********************************************************************
Function Name: PrintScene
Purpose: To display the round information on console at all times
Parameters:human and computer player objects, engine tile, game object
Return Value: none
Algorithm:
		1) ASCII printing to display the round information
		2) used setw() and train sizes to correctly format the trains
********************************************************************* */

void Round::PrintScene(Human a_HumanPlayer, Computer a_ComputerPlayer, Tile a_engine, Game a_gameObject) {

	cout << "Round #: " << mRoundNumber;
	cout << left << setw(25) << " ";
	PrintBoneYard();
	cout << left << setw(25) << " ";
	cout << "Round Score: " << right << setw(25) << "Game Score: " << endl;
	mHumanScore = a_HumanPlayer.GetPlayerScore(a_HumanPlayer.GetPlayerHand());
	mComputerScore = a_ComputerPlayer.GetPlayerScore(a_ComputerPlayer.GetPlayerHand());

	cout << "Human Score: " << right << setw(18) << mHumanScore << right << setw(25) << a_gameObject.GetHumanScore() << endl;
	cout << "Computer Score: " << right << setw(15) << mComputerScore << right << setw(25) << a_gameObject.GetComputerScore() << endl;
	cout << endl;

	cout << "Human Hand: ";
	a_HumanPlayer.PrintHumanHand();

	cout << endl;

	cout << "Computer Hand: ";
	a_ComputerPlayer.PrintComputerHand();

	cout << endl;

	int cTrainSize = mComputerTrain.GetTrain().size();
	int hTrainSize = mHumanTrain.GetTrain().size();
	int mTrainSize = mMexicanTrain.GetTrain().size();

	int engineTab = (cTrainSize * 7) + 6;
	if (mComputerTrain.TrainHasMarker()) engineTab = (cTrainSize * 7) + 6 + 5;
	cout << left << setw(engineTab) << " ";

	cout << a_engine.GetTileLeft() << endl;

	cout << left << setw(5) << " ";
	if (mComputerTrain.TrainHasMarker()) cout << "--M--";

	for (int i = cTrainSize; i > 0; i--) {
		cout << "-[" << mComputerTrain.GetTrain()[i - 1].PrintTileReverse() << "]-";
	}
	cout << "-|-";

	for (int i = 0; i < hTrainSize; i++) {
		cout << "-[" << mHumanTrain.GetTrain()[i].PrintTile() << "]-";
	}
	if (mHumanTrain.TrainHasMarker()) cout << "--M--";
	cout << endl;

	cout << left << setw(engineTab) << " ";
	cout << a_engine.GetTileRight() << endl;

	cout << left << setw(engineTab) << " ";
	cout << "|" << endl;
	cout << left << setw(engineTab-2) << " ";
	for (int i = 0; i < mTrainSize; i++) {
		cout << "[" << mMexicanTrain.GetTrain()[i].PrintTile() << "]-";
	}
	cout << "\n" << endl;
}


/* *********************************************************************
Function Name: SaveGame
Purpose: To save the current game to the file
Parameters: Human, computer player object, engine tile, current player index, 
			current game object
Return Value: none
Algorithm:
		1) appends all trains, hands, boneyards, round #, and score information
			in a string in one standard format for the game
		2) Get the next player from the a_PlayerIndex argument value
		3) Concatenate all the strings to one big string and write the string
			to the file
Assistance Received: none
********************************************************************* */

void Round::SaveGame(Human a_HumanPlayer, Computer a_ComputerPlayer, Tile a_engine, int a_PlayerIndex, Game& a_gameObject) {

	//save all the game information in a string in parts

	string round = "Round: " + to_string(mRoundNumber) + "\n";
	string computerState = "Computer:\nScore: " + to_string(a_gameObject.GetComputerScore()) + "\n";
	string computerHand = "Hand:";
	string computerTrain = "Train:";

	//if computer train has marker add "M" to the computerTrain string
	if (mComputerTrain.TrainHasMarker()) computerTrain = "Train: M";

	for (int i = 0; i < a_ComputerPlayer.GetPlayerHand().size(); i++) {
		computerHand = computerHand + " " + a_ComputerPlayer.GetPlayerHand()[i].PrintTile();
	}

	for (int i = mComputerTrain.GetTrain().size(); i > 0; i--) {
		computerTrain = computerTrain + " " + mComputerTrain.GetTrain()[i - 1].PrintTileReverse();
	}

	computerTrain = computerTrain + " " + a_engine.PrintTile() + "\n";

	computerState = computerState + computerHand + "\n" + computerTrain;

	string humanState = "Human:\nScore: " + to_string(a_gameObject.GetHumanScore()) + "\n";
	string humanHand = "Hand:";
	string humanTrain = "Train:";

	for (int i = 0; i < a_HumanPlayer.GetPlayerHand().size(); i++) {
		humanHand = humanHand + " " + a_HumanPlayer.GetPlayerHand()[i].PrintTile();
	}

	humanTrain = humanTrain + " " + a_engine.PrintTile();
	for (int i = 0; i < mHumanTrain.GetTrain().size(); i++) {
		humanTrain = humanTrain + " " + mHumanTrain.GetTrain()[i].PrintTile();
	}
	//if human train has marker add it to the end of human train string
	if(mHumanTrain.TrainHasMarker()) humanTrain = humanTrain + " M\n";
	else humanTrain = humanTrain + "\n";
	
	humanState = humanState + humanHand + "\n" + humanTrain;

	string mexicanTrain = "Mexican Train:";
	for (int i = 0; i < mMexicanTrain.GetTrain().size(); i++) {
		mexicanTrain = mexicanTrain + " " + mMexicanTrain.GetTrain()[i].PrintTile();
	}
	mexicanTrain = mexicanTrain + "\n";

	string boneyard = "Boneyard:";
	for (int i = 0; i < mBoneYard.size(); i++) {
		boneyard = boneyard + " " + mBoneYard[i].PrintTile();
	}
	boneyard = boneyard + "\n";

	string nextPlayer = "Next Player:";

	//player index 1 is always computer's and 0 is always human's, if 1 next player is computer
	if (a_PlayerIndex == 1) {
		nextPlayer = nextPlayer + "\n" + "Computer";
	}
	//if 0 next player is human
	else {
		nextPlayer = nextPlayer + "\n" + "Human";
	}

	//append all the information saved in different string variables to one string variable which will be wrote to file
	string gameState = round + computerState + humanState + mexicanTrain + boneyard + nextPlayer;

	string filename;
	cout << "Please enter a filename (with .txt extension) you would like to save the game to. " << endl;
	cin >> filename;

	// Create and open a text file
	ofstream GameFile(filename);

	// Write the big string with all information to the file
	GameFile << gameState;

	// Close the file
	GameFile.close();
}


/* *********************************************************************
Function Name: StartGameFromFile
Purpose: To start an old game from a file
Parameters:Human, computer player object, current game object
Return Value: none
Algorithm:
		1) Open the file, read one line at a time
		2) split the line by space and add each word to a vector (gameinfo)
		3) retreive the game information from the gameinfo vector by calculating
			their respective indices, eg: round# will always be on gameinfo[1]
		4) after retreving the information, parse them in correct type and data
			structure, eg( round # to integer, trains to vectors of tiles, etc)
		5) After structuring the data, set them to players objects, train objects,
			boneyards, etc.

Assistance Received: none
********************************************************************* */

void Round::StartGameFromFile(Human& a_HumanPlayer, Computer& a_ComputerPlayer, Game& a_gameObject) {

	string fileName;
	cout << "Please enter file name to read the game data from. " << endl;
	cin >> fileName;

	// Read from the text file
	ifstream ReadFile(fileName);

	if (ReadFile.is_open()) {

		// Create a text string, which is used to output the text file
		string gameData, splitWord;
		vector<string> gameInfo;


		// Use a while loop together with the getline() function to read the file line by line
		while (getline(ReadFile, gameData)) {
			// Output the text from the file
			istringstream dataSplit(gameData);
			while (dataSplit >> splitWord) {
				gameInfo.push_back(splitWord);
			}
		}

		a_gameObject.SetComputerGameScore(stoi(gameInfo[4]));
		mRoundNumber = stoi(gameInfo[1]);
		
		// using CreateTilesVector function to create the vector of tiles for player hands, providing the starting index
		vector<Tile> ComputerHand = CreateTilesVector(6, "Train:", gameInfo, "hand");

		vector<Tile> ComputerTrain = CreateTilesVector(5 + ComputerHand.size() + 2, "Human:", gameInfo, "C-train");

		vector<Tile> HumanHand = CreateTilesVector(5 + ComputerHand.size() + 1 + ComputerTrain.size() + 5, "Train:", gameInfo, "hand");

		//computing the start index for h-train since it will be determines by computer's hand, train, and human hands size in the file
		int HTrainStartIndex = 5 + ComputerHand.size() + 1 + ComputerTrain.size() + 4 + HumanHand.size() + 2;

		vector<Tile> HumanTrain = CreateTilesVector(HTrainStartIndex, "Mexican", gameInfo, "Htrain");

		int MtrainStartIndex = HTrainStartIndex + HumanTrain.size() + 2;

		vector<Tile> MexicanTrain = CreateTilesVector(MtrainStartIndex, "Boneyard:", gameInfo, "Mtrain");

		int BoneyardStartIndex = MtrainStartIndex + MexicanTrain.size() + 1;

		vector<Tile> Boneyard = CreateTilesVector(BoneyardStartIndex, "Next", gameInfo, "boneyard");

		//after structuring the data, setting them to the member variables of round class, trains, and players objects

		SetBoneYard(Boneyard);

		int humanScoreIndex = 5 + ComputerHand.size() + 1 + ComputerTrain.size() + 3;
		a_gameObject.SetHumanGameScore(stoi(gameInfo[humanScoreIndex]));
		
		a_ComputerPlayer.SetComputerHand(ComputerHand);

		//adding trains tiles from file to the actual computer train object

		for (int i = ComputerTrain.size() - 2; i >= 0; i--) {
			mComputerTrain.AddTileOnTrain(ComputerTrain[i]);
		}

		a_HumanPlayer.SetHumanHand(HumanHand);
		for (int i = 1; i < HumanTrain.size(); i++) {
			mHumanTrain.AddTileOnTrain(HumanTrain[i]);
		}

		for (int i = 0; i < MexicanTrain.size(); i++) {
			mMexicanTrain.AddTileOnTrain(MexicanTrain[i]);
		}

		//getting the next player from the file
		string nextPlayer = gameInfo[gameInfo.size() - 1];
		if (nextPlayer == "Human") mTurnHuman = true;
	}
	//validating user input
	else {
		cout << "Sorry, could not open the given file." << endl;
		exit(0);
	}

	// Close the file
	ReadFile.close();
}

/* *********************************************************************
Function Name: CreateTilesVector
Purpose: Creates a vector of tile from a given vector of string
Parameters: startindex, endString, stringVector, tileFor -> whom are we creating
			the tile vector for (computer, human, hands)
Return Value: 
Algorithm:
		1) loops through a vector of string from a start index, until an
			end string is reached
		2) Converts the string tile to actual tile object using MakeTile function
		3) adds these tiles to a tileVector vector, which is returned at the end

Assistance Received: none
********************************************************************* */

vector<Tile> Round::CreateTilesVector(int a_startIndex, string a_endString, vector<string> a_stringVector, string a_tileFor) {
	vector<Tile> tileVector;
	Tile tileobj(-1, -1);

	for (int i = a_startIndex; i < a_stringVector.size(); i++) {
		if (a_stringVector[i] == a_endString) break;
		tileVector.push_back(tileobj.MakeTile(a_stringVector[i], a_tileFor));
	}

	return tileVector;
}