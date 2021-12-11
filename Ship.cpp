#include "Ship.h"

Ship::Ship(int size)
{
	Size = size;
	shipStatEnum = ShipStatEnum::Notdeployed;
	shipOriEnum = ShipOriEnum::down;
}

void Ship::clear()
{
	shipStatEnum = ShipStatEnum::Notdeployed;
	shipOriEnum = ShipOriEnum::down;
	for (int i = 0; i < (sizeof(ShipNodes) / sizeof(ShipNodes[0])); i++)
	{
		ShipNodes[i].clear();
	}
}

bool Ship::IsAlive() 
{
	bool isAlive = false;
	for (int i = 0; i < Size; i++)
	{
		if (ShipNodes[i].nodeStatEnum != NodeStatEnum::hit) 
		{
			isAlive = true;
		}
	}
	shipStatEnum = isAlive ?  ShipStatEnum::alive : ShipStatEnum::destroyed;
	return isAlive;
} 

bool Ship::IsHitOnThisShip(int x, int y) 
{
	bool isHitOnThisShip = false;
	for (int i = 0; i < Size; i++)
	{
		if (ShipNodes[i].X == x && ShipNodes[i].Y == y)
		{
			ShipNodes[i].nodeStatEnum = NodeStatEnum::hit;
			isHitOnThisShip = true;
		}
	}
	return isHitOnThisShip;

}



