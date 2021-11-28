#include "Player.h"


Player::Player(bool isHuman)
{
	IsHuman = isHuman;
	Name = isHuman ? "Player" : "Computer";
	PlayerBoard.Clear(PlayerBoard.GameBoard);
	PlayerBoard.init(PlayerBoard.GameBoard);
}

void Player::placeShip(int x, int y, Ship(&shipToPlace), ShipOriEnum shipOriEnum, Node(&gameBoard)[BoardSize][BoardSize])
{
	shipToPlace.shipStatEnum = ShipStatEnum::alive;
	switch (shipOriEnum)
	{
	case ShipOriEnum::up:
		for (int i = 0; i < shipToPlace.Size; i++)
		{
			gameBoard[x-i][y].nodeStatEnum = NodeStatEnum::ocupied;
			shipToPlace.ShipNodes[i] = gameBoard[x - i][y];
			MarkUnplacable(x - i, y, gameBoard);
		}
		break;
	case ShipOriEnum::down:
		for (int i = 0; i < shipToPlace.Size; i++)
		{
			gameBoard[x+i][y].nodeStatEnum = NodeStatEnum::ocupied;
			shipToPlace.ShipNodes[i] = gameBoard[x + i][y];
			MarkUnplacable(x + i, y, gameBoard);
		}
		break;
	case ShipOriEnum::left:
		for (int i = 0; i < shipToPlace.Size; i++)
		{
			gameBoard[x][y-i].nodeStatEnum = NodeStatEnum::ocupied;
			shipToPlace.ShipNodes[i] = gameBoard[x][y - i];
			MarkUnplacable(x, y - i, gameBoard);
		}
		break;
	case ShipOriEnum::right:
		for (int i = 0; i < shipToPlace.Size; i++)
		{
			gameBoard[x][y+i].nodeStatEnum = NodeStatEnum::ocupied;
			shipToPlace.ShipNodes[i] = gameBoard[x][y + i];
			MarkUnplacable(x, y + i, gameBoard);
		}
		break;
	}
	
	
}

bool Player::HasRemainningShips()
{
	bool HasShips = false;
	for (int i = 0; i < (sizeof(smallShips) / sizeof(smallShips[0])); i++)
	{
		if (smallShips[i].shipStatEnum == ShipStatEnum::alive)
			HasShips = true;
	}
	for (int i = 0; i < (sizeof(mediumShips) / sizeof(mediumShips[0])); i++)
	{
		if (mediumShips[i].shipStatEnum == ShipStatEnum::alive)
			HasShips = true;
	}
	for (int i = 0; i < (sizeof(largeShips) / sizeof(largeShips[0])); i++)
	{
		if (largeShips[i].shipStatEnum == ShipStatEnum::alive)
			HasShips = true;
	}
	for (int i = 0; i < (sizeof(xlShips) / sizeof(xlShips[0])); i++)
	{
		if (xlShips[i].shipStatEnum == ShipStatEnum::alive)
			HasShips = true;
	}
	return HasShips;
}

void Player::MarkUnplacable(int x, int y, Node(&gameBoard)[BoardSize][BoardSize])
{
	if (x - 1 >= 0  && gameBoard[x - 1][y].nodeStatEnum != NodeStatEnum::ocupied) 
	{
		gameBoard[x - 1][y].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (x + 1 <= BoardSize && gameBoard[x + 1][y].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x + 1][y].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y - 1 >= 0 && x - 1 >= 0 && gameBoard[x - 1][y - 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x - 1][y - 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y + 1 <= BoardSize && x + 1 <= BoardSize && gameBoard[x + 1][y + 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x + 1][y + 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y + 1 <= BoardSize && x - 1 >= 0 && gameBoard[x - 1][y + 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x - 1][y + 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y - 1 >= 0 && x + 1 <= BoardSize && gameBoard[x + 1][y - 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x + 1][y - 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y + 1 <= BoardSize && gameBoard[x][y + 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x][y + 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y - 1 >= 0 && gameBoard[x][y - 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x][y - 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
}

