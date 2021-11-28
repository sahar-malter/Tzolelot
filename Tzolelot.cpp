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

int RandomNumber(int max)
{
	int randNum = (rand() % max);

	return randNum;
}

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
	int random = RandomNumber(2);
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

bool isPlacmentOver(Player& currentPlayer)
{
	bool PlacmentOver = true;
	for (int i = 0; i < (sizeof(currentPlayer.smallShips) / sizeof(currentPlayer.smallShips[0])); i++)
	{
		if (currentPlayer.smallShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
			return false;
	}
	for (int i = 0; i < (sizeof(currentPlayer.mediumShips) / sizeof(currentPlayer.mediumShips[0])); i++)
	{
		if (currentPlayer.mediumShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
			return false;
	}
	for (int i = 0; i < (sizeof(currentPlayer.largeShips) / sizeof(currentPlayer.largeShips[0])); i++)
	{
		if (currentPlayer.largeShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
			return false;
	}
	for (int i = 0; i < (sizeof(currentPlayer.xlShips) / sizeof(currentPlayer.xlShips[0])); i++)
	{
		if (currentPlayer.xlShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
			return false;
	}
	return PlacmentOver;
}

bool IsShipFitInBoard(int x, int y, int size, ShipOriEnum shipOriEnum, Player& currentPlayer)
{
	bool FitInBoards = true;
	switch (shipOriEnum)
	{
	case ShipOriEnum::up:
		
		if (x - size < 0)
		{
			FitInBoards = false;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (currentPlayer.PlayerBoard.GameBoard[x - i][y].nodeStatEnum != NodeStatEnum::empty) 
			{
				FitInBoards = false;
				break;
			}
		}
		break;
	case ShipOriEnum::down:

		if (x + size >= BoardSize)
		{
			FitInBoards = false;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (currentPlayer.PlayerBoard.GameBoard[x + i][y].nodeStatEnum != NodeStatEnum::empty)
			{
				FitInBoards = false;
				break;
			}
		}
		break;
	case ShipOriEnum::left:

		if (y - size < 0)
		{
			FitInBoards = false;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (currentPlayer.PlayerBoard.GameBoard[x][y - i].nodeStatEnum != NodeStatEnum::empty)
			{
				FitInBoards = false;
				break;
			}
		}
		break;
	case ShipOriEnum::right:

		if (y + size >= BoardSize)
		{
			FitInBoards = false;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (currentPlayer.PlayerBoard.GameBoard[x][y + i].nodeStatEnum != NodeStatEnum::empty)
			{
				FitInBoards = false;
				break;
			}
		}
		break;
	}

	return FitInBoards;
}

void PlaceShipRandomlly(Player& currentPlayer)
{
	int randomX = RandomNumber(BoardSize);
	int randomY = RandomNumber(BoardSize);

	for (int i = 0; i < (sizeof(currentPlayer.smallShips) / sizeof(currentPlayer.smallShips[0])); i++)
	{
		if (currentPlayer.smallShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
		{
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.smallShips[i].Size, ShipOriEnum::up, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.smallShips[i], ShipOriEnum::up, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.smallShips[i].Size, ShipOriEnum::down, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.smallShips[i], ShipOriEnum::down, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.smallShips[i].Size, ShipOriEnum::right, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.smallShips[i], ShipOriEnum::right, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.smallShips[i].Size, ShipOriEnum::left, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.smallShips[i], ShipOriEnum::left, currentPlayer.PlayerBoard.GameBoard);
				return;
			}

		}
	}
	for (int i = 0; i < (sizeof(currentPlayer.mediumShips) / sizeof(currentPlayer.mediumShips[0])); i++)
	{
		if (currentPlayer.mediumShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
		{
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.mediumShips[i].Size, ShipOriEnum::up, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.mediumShips[i], ShipOriEnum::up, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.mediumShips[i].Size, ShipOriEnum::down, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.mediumShips[i], ShipOriEnum::down, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.mediumShips[i].Size, ShipOriEnum::right, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.mediumShips[i], ShipOriEnum::right, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.mediumShips[i].Size, ShipOriEnum::left, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.mediumShips[i], ShipOriEnum::left, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
		}
	}
	for (int i = 0; i < (sizeof(currentPlayer.largeShips) / sizeof(currentPlayer.largeShips[0])); i++)
	{
		if (currentPlayer.largeShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
		{
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.largeShips[i].Size, ShipOriEnum::up, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.largeShips[i], ShipOriEnum::up, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.largeShips[i].Size, ShipOriEnum::down, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.largeShips[i], ShipOriEnum::down, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.largeShips[i].Size, ShipOriEnum::right, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.largeShips[i], ShipOriEnum::right, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.largeShips[i].Size, ShipOriEnum::left, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.largeShips[i], ShipOriEnum::left, currentPlayer.PlayerBoard.GameBoard);
				return;
			}

		}
	}
	for (int i = 0; i < (sizeof(currentPlayer.xlShips) / sizeof(currentPlayer.xlShips[0])); i++)
	{
		if (currentPlayer.xlShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
		{
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.xlShips[i].Size, ShipOriEnum::up, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.xlShips[i], ShipOriEnum::up, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.xlShips[i].Size, ShipOriEnum::down, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.xlShips[i], ShipOriEnum::down, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.xlShips[i].Size, ShipOriEnum::right, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.xlShips[i], ShipOriEnum::right, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
			if (IsShipFitInBoard(randomX, randomY, currentPlayer.xlShips[i].Size, ShipOriEnum::left, currentPlayer))
			{
				currentPlayer.placeShip(randomX, randomY, currentPlayer.xlShips[i], ShipOriEnum::left, currentPlayer.PlayerBoard.GameBoard);
				return;
			}
		}
	}
	PlaceShipsLoop();
}

void PlaceShipsLoop()
{
	if (gameState != GameState::Placment) 
	{
		Gameloop();
	}

	if (isPlacmentOver(Computer))
	{
		DrawBoards();
	}
	else 
	{
		PlaceShipRandomlly(Computer);
	}

}

void InitGame()
{
	SetStartingPlayer();
	cout << "Press any key";
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
