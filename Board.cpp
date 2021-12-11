#include "Board.h"
#include <iostream>
#include "Node.h"



using namespace std;


Board::Board()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Coloring
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

void Board::Draw(Node(&gameBoard)[BoardSize][BoardSize],bool isPlayer )
{
	if (isPlayer) 
	{
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			switch (gameBoard[i][j].nodeStatEnum)
			{
			case NodeStatEnum::empty:
				SetConsoleTextAttribute(hConsole, 7);
				cout << "[";
				SetConsoleTextAttribute(hConsole, 3);
				cout << "~";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "]";
				break;
			case NodeStatEnum::ocupied:
				SetConsoleTextAttribute(hConsole, 7);
				cout << "[";
				SetConsoleTextAttribute(hConsole, 2);
				cout << "@";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "]";
				break;
			case NodeStatEnum::unplacable:
				SetConsoleTextAttribute(hConsole, 7);
				cout << "[";
				SetConsoleTextAttribute(hConsole, 8);
				cout << "~";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "]";
				break;
			case NodeStatEnum::hit:
				SetConsoleTextAttribute(hConsole, 7);
				cout << "[";
				SetConsoleTextAttribute(hConsole, 4);
				cout << "@";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "]";
				break;
			case NodeStatEnum::attempted:
				SetConsoleTextAttribute(hConsole, 7);
				cout << "[";
				SetConsoleTextAttribute(hConsole, 14);
				cout << "*";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "]";
				break;
			default:
				cout << "[~]";
				break;
			}
		}
		cout << endl;
	}
	}
	else 
	{
		for (int i = 0; i < BoardSize; i++)
		{
			for (int j = 0; j < BoardSize; j++)
			{
				switch (gameBoard[i][j].nodeStatEnum)
				{
				case NodeStatEnum::empty:
					SetConsoleTextAttribute(hConsole, 7);
					cout << "[";
					SetConsoleTextAttribute(hConsole, 3);
					cout << "~";
					SetConsoleTextAttribute(hConsole, 7);
					cout << "]";
					break;
				case NodeStatEnum::ocupied:
					SetConsoleTextAttribute(hConsole, 7);
					cout << "[";
					SetConsoleTextAttribute(hConsole, 3);
					cout << "~";
					SetConsoleTextAttribute(hConsole, 7);
					cout << "]";
					break;
				case NodeStatEnum::unplacable:
					SetConsoleTextAttribute(hConsole, 7);
					cout << "[";
					SetConsoleTextAttribute(hConsole, 3);
					cout << "~";
					SetConsoleTextAttribute(hConsole, 7);
					cout << "]";
					break;
				case NodeStatEnum::hit:
					SetConsoleTextAttribute(hConsole, 7);
					cout << "[";
					SetConsoleTextAttribute(hConsole, 4);
					cout << "@";
					SetConsoleTextAttribute(hConsole, 7);
					cout << "]";
					break;
				case NodeStatEnum::attempted:
					SetConsoleTextAttribute(hConsole, 7);
					cout << "[";
					SetConsoleTextAttribute(hConsole, 14);
					cout << "*";
					SetConsoleTextAttribute(hConsole, 7);
					cout << "]";
					break;
				default:
					cout << "[~]";
					break;
				}
			}
			cout << endl;
		}
	}
}
