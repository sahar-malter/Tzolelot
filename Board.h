#pragma once
#include "Node.h"
#include <windows.h>



const int BoardSize = 10;
static HANDLE  hConsole; // for colors

class Board
{
public:
	Board();
	Node GameBoard[BoardSize][BoardSize];
	void init(Node(&gameBoard)[BoardSize][BoardSize]);
	void Clear(Node(&gameBoard)[BoardSize][BoardSize]);
	void Draw(Node(&gameBoard)[BoardSize][BoardSize],bool isPlayer);


};

