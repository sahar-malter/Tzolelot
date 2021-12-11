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
	bool shouldPlayAgain;
	bool myTurn;
	std::string Name;

	void placeShip(int x, int y, Ship(&shipToPlace), ShipOriEnum shipOriEnum, Node(&gameBoard)[BoardSize][BoardSize]); // place ship on the board
	bool HasRemainningShips(); // checks if any ship is still alive 
	void MarkUnplacable(int x, int y, Node(&gameBoard)[BoardSize][BoardSize]); // iterate around a given node and mark all the unplacable places around it
	void MarkAttempted(Ship(&shipToMarkAround), Node(&gameBoard)[BoardSize][BoardSize]); // iterate around a given ships nodes and mark all the attempted (cant bomb there) places around it
	bool isPlacementOver(bool ShouldReport); // is there any ships left to place on the board?
	void PlaceShipRandomlly(); // computer place ships on board algoritem 
	bool IsShipFitInBoard(int x, int y, int size, ShipOriEnum shipOriEnum); // is the ship given is in the bounds of the game?
	int RandomNumber(int max); // return a randome number from 0 up to given int
	void HandlePlayerInput(Ship(&shipToPlace)); // checks all the player input when placing ships and act accordinglly 
	void ChooseShipToPlace();
	void RunOverShipsToRemark(); // iterate over all the ships and call "MarkUnplacable", this enable to place a ship you allready placed
	void GuessPointOnBoard(Node(&gameBoard)[BoardSize][BoardSize], Player(&otherPlayer)); // computer guessing random places on board
	void HandleHit(int x, int y, Node(&gameBoard)[BoardSize][BoardSize], Player(&otherPlayer)); // when either side hit the other, handle all that
	void ChooseNodeToHit(Player(&otherPlayer)); // player input handeling when in battle
};

