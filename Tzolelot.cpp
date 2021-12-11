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
//Player& currentPlayer = player;
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
	

}

void GameOver()
{
	cout << "Game Over, thank god..." << endl;
	system("pause");
	return;
}

void SetStartingPlayer()
{
	int random = Computer.RandomNumber(2);
	if (random == 0)
	{
		player.myTurn = true;
		Computer.myTurn = false;
		cout << player.Name << " will start" << endl;
	}
	else
	{
		player.myTurn = false;
		Computer.myTurn = true;
		cout << Computer.Name << " will start" << endl;
	}
}

void HandleTurns() 
{
	if (player.myTurn)
	{
		if (player.shouldPlayAgain)
		{
			player.shouldPlayAgain = false;
			player.myTurn = true;
			Computer.myTurn = false;
		}
		else 
		{
			player.myTurn = false;
			Computer.myTurn = true;
		}
	}
	else
	{
		if (Computer.shouldPlayAgain)
		{
			Computer.shouldPlayAgain = false;
			Computer.myTurn = true;
			player.myTurn = false;
		}
		else
		{
			player.myTurn = true;
			Computer.myTurn = false;
		}
	}
}
void BattleLoop() 
{
	if (gameState != GameState::battle)
	{
		Gameloop();
	}
	if (!player.HasRemainningShips())
	{
		cout << Computer.Name << " WON !!!! " << endl;
		gameState = GameState::over;
	}
	else if (!Computer.HasRemainningShips())
	{
		cout << player.Name << " WON !!!! " << endl;
		gameState = GameState::over;
	}
	else
	{
		HandleTurns();
		if (player.myTurn)
		{
			player.ChooseNodeToHit(Computer);
		}
		else
		{
			Computer.GuessPointOnBoard(player.PlayerBoard.GameBoard, player);
		}
		system("pause");
		DrawBoards();
	}
	    Gameloop();
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
		cout << " Placment is over - lets battle  " << endl;
		gameState = GameState::battle;
		DrawBoards();
		Gameloop();
	}
	Gameloop();


}

void InitGame()
{
    cout << " Welcome to Battleship cpp  " << endl;
    cout << " The rules are simple, so i will not bother to explain :D " << endl;
    cout << " Choose your name - dont be a dick and break the game " << endl;
	cin >> player.Name;
	SetStartingPlayer();
	system("pause");
	DrawBoards();
	system("pause");
	gameState = GameState::Placment;
	Gameloop();
}

void Gameloop() 
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


int main()
{
	srand(time(NULL));  // Random seed
	gameState = GameState::init;
	Gameloop();
	return 0;
}
