// Tzolelot.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <windows.h>
#include <iostream>
#include "Board.h"
#include <iostream>
#include "Node.h"
#include "Player.h"

using namespace std;
Player player(true);
Player Computer(false);


int RandomNumber(int max)
{
	int randNum = (rand() % max);

	return randNum;
}

void GameOver()
{

}

void Gameloop() 
{

	// we should have like 4 functions that run in a loop,
	// checking if the game is over
	// asking the player to give input
	// check the input and act accordinglly
	// print the result
}
void SetStartingPlayer() 
{
	int random = RandomNumber(2);
	Computer.MyTurn = random != 0;
	if (random == 0)
	{
	player.MyTurn = true;
	Computer.MyTurn = false;
	cout << player.Name << " will start";
	}
	else 
	{
		player.MyTurn = false;
		Computer.MyTurn = true;
		cout << Computer.Name << " will start";
	}
}

void InitGame()
{
	SetStartingPlayer();
	Gameloop();
}


int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Coloring
	srand(time(NULL));  // Random seed
	InitGame();

}
