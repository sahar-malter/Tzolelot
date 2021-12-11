#pragma once
#include "Node.h"

enum class ShipStatEnum
	{
		Notdeployed = 0,
		alive = 1,
		destroyed = 2
	};
enum class ShipOriEnum{
	up = 0,
	down = 1,
	left = 2,
	right = 3
};

class Ship
{
public:
	Ship(int size);
	int Size;
	ShipStatEnum shipStatEnum;
	ShipOriEnum shipOriEnum;
	Node ShipNodes[5];
	void clear();
	bool IsAlive();// has any unhit nodes?
	bool IsHitOnThisShip(int x, int y);// recive x and y to check if this ship nodes match them, if yes then this ship is hit. 
};


