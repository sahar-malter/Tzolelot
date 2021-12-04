#pragma once
#include "Ship.h"
#include "Board.h"
#include <string>
using namespace std;


class Player
{
public:
	Player(bool isHuman);
	Ship smallShips[1] { 2 };
	Ship mediumShips[2] { 3,3 };
	Ship largeShips[1] { 4 };
	Ship xlShips[1] { 5 };
	Board PlayerBoard;
	bool IsHuman;
	std::string Name;
	bool MyTurn = false;

	void placeShip(int x, int y, Ship(&shipToPlace), ShipOriEnum shipOriEnum, Node(&gameBoard)[BoardSize][BoardSize]);
	bool HasRemainningShips();
	void MarkUnplacable(int x, int y, Node(&gameBoard)[BoardSize][BoardSize]);
	bool isPlacementOver(bool ShouldReport);
	void PlaceShipRandomlly();
	bool IsShipFitInBoard(int x, int y, int size, ShipOriEnum shipOriEnum);
	int RandomNumber(int max);
	void HandlePlayerInput(Ship(&shipToPlace));
	void ChooseShipToPlace();
	void RunOverShipsToRemark();
};

