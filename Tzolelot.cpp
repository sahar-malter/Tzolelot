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
void Gameloop();
void PlaceShipsLoop();

enum class GameState
{
	init,
	Placment,
	battle,
	over
};
GameState gameState;


void DrawBoards()
{
	system("cls");
	cout << endl;
	cout << "        Player Board" << endl;
	player.PlayerBoard.Draw(player.PlayerBoard.GameBoard, true);
	cout << endl;
	cout << "        Computer Board" << endl;
	Computer.PlayerBoard.Draw(Computer.PlayerBoard.GameBoard, true); // should be false to hide the computer ships
	system("pause");

}

void GameOver()
{

}

void SetStartingPlayer()
{
	int random = Computer.RandomNumber(2);
	Computer.MyTurn = random != 0;
	if (random == 0)
	{
		player.MyTurn = true;
		Computer.MyTurn = false;
		cout << player.Name << " will start" << endl;
	}
	else
	{
		player.MyTurn = false;
		Computer.MyTurn = true;
		cout << Computer.Name << " will start" << endl;
	}
}

void BattleLoop() 
{
	if (gameState != GameState::battle)
	{
		Gameloop();
	}
	if (!player.HasRemainningShips() || !Computer.HasRemainningShips()) 
	{
		gameState = GameState::over;
		Gameloop();
	}
	DrawBoards();
}

void PlaceShipsLoop()
{
	if (gameState != GameState::Placment)
	{
		Gameloop();
	}

	if (!Computer.isPlacementOver(false))
	{
		Computer.PlaceShipRandomlly();
	}
	if (!player.isPlacementOver(false))
	{
		player.ChooseShipToPlace();
	}
	else
	{
		gameState = GameState::battle;
		Gameloop();
	}
	PlaceShipsLoop();


}

void InitGame()
{
	SetStartingPlayer();
	system("pause");
	DrawBoards();
	gameState = GameState::Placment;
	Gameloop();
}

void Gameloop() 
{
	while (gameState != GameState::over)
	{
		switch (gameState)
		{
		case GameState::init:
			InitGame();
			break;
		case GameState::Placment:
			PlaceShipsLoop();
			break;
		case GameState::battle:
			BattleLoop();
			break;
		case GameState::over:
			GameOver();
			break;
		default:
			break;
		}
	}
	// we should have like 4 functions that run in a loop,
	// checking if the game is over
	// asking the player to give input
	// check the input and act accordinglly
	// print the result
}


int main()
{
	srand(time(NULL));  // Random seed
	gameState = GameState::init;
	Gameloop();
	return 0;
}
