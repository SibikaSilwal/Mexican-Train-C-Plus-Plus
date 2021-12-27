/************************************************************
* Name:  Sibika Silwal										*
* Project : Project 1, C++ Mexican Train 					*
* Class : CMPS 366 - OPL									*
* Date : 09/29/2021											*
************************************************************/

#include <iostream>
#include"Deck.h"
#include"Game.h"
#include<stdio.h>
#include<string>
#include<algorithm>

using namespace std;

// MexicanTrain.cpp : This file contains the 'main' function. Program execution begins and ends here.
int main()
{
    //Create game object
    Game newGame;

    //strart new game
    newGame.StartGame(&newGame);

    string nextRound = "Y";

    //ask user if they want to play next game
    while (nextRound == "Y") {

        cout << "Do you want to play next round?(Y/N)" << endl;

        cin >> nextRound;
        transform(nextRound.begin(), nextRound.end(), nextRound.begin(), ::toupper);

        //validate input
        if (nextRound != "Y" && nextRound != "N") {
            cout << "Please enter 'Y' to play next round and 'N' to quit." << endl;
        }
        //if yes continue the game with next round
        if (nextRound == "Y") {
            newGame.ContinueGame(&newGame);
        }
        //if not display final scores and the winner
        if (nextRound == "N") {

            cout << "Final scores are: \nHuman: " << newGame.GetHumanScore() << " \nComputer: " << newGame.GetComputerScore() << endl;

            if (newGame.GetHumanScore() < newGame.GetComputerScore())
                cout << "\n>> Congratulations you won the game :) !!";

            else if (newGame.GetHumanScore() == newGame.GetComputerScore())
                cout << "\n>> No body won the game. It's a tie between you and the computer :|" << endl;

            else
                cout << "\n >> You lost the game :( Computer won the game." << endl;
        }
    }
    

}

