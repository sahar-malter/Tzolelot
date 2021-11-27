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
	switch (shipOriEnum)
	{
	case ShipOriEnum::up:
		for (int i = 0; i < shipToPlace.Size; i++)
		{
			gameBoard[x-i][y].nodeStatEnum = NodeStatEnum::ocupied;
		}
		break;
	case ShipOriEnum::down:
		for (int i = 0; i < shipToPlace.Size; i++)
		{
			gameBoard[x+i][y].nodeStatEnum = NodeStatEnum::ocupied;
		}
		break;
	case ShipOriEnum::left:
		for (int i = 0; i < shipToPlace.Size; i++)
		{
			gameBoard[x][y-i].nodeStatEnum = NodeStatEnum::ocupied;
		}
		break;
	case ShipOriEnum::right:
		for (int i = 0; i < shipToPlace.Size; i++)
		{
			gameBoard[x][y+i].nodeStatEnum = NodeStatEnum::ocupied;
		}
		break;
	}
	
	
}

