#include "Board.h"
#include <iostream>
#include "Node.h"



using namespace std;


Board::Board()
{
}

void Board::init(Node(&gameBoard)[BoardSize][BoardSize])
{
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			gameBoard[i][j].X = i;
			gameBoard[i][j].Y = j;
		}
	}
}

void Board::Clear(Node(&gameBoard)[BoardSize][BoardSize])
{
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			gameBoard[i][j].X = 0;
			gameBoard[i][j].Y = 0;
			gameBoard[i][j].nodeStatEnum = NodeStatEnum::empty;
		}
	}
}

void Board::Draw(Node(&gameBoard)[BoardSize][BoardSize])
{
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			switch (gameBoard[i][j].nodeStatEnum)
			{
			case NodeStatEnum::empty:
				SetConsoleTextAttribute(hConsole, 5);
				cout << "[0]";
				SetConsoleTextAttribute(hConsole, 7);
				break;
			case NodeStatEnum::ocupied:
				SetConsoleTextAttribute(hConsole, 2);
				cout << "[1]";
				SetConsoleTextAttribute(hConsole, 7);
				break;
			case NodeStatEnum::hit:
				SetConsoleTextAttribute(hConsole, 3);
				cout << "[2]";
				SetConsoleTextAttribute(hConsole, 7);
				break;
			default:
				cout << "[ ]";
				break;
			}
		}
		cout << endl;
	}
}
