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


