#include "Player.h"
#include <iostream>



Player::Player(bool isHuman)
{
	IsHuman = isHuman;
	Name = isHuman ? "Player" : "Computer";
	PlayerBoard.Clear(PlayerBoard.GameBoard);
	PlayerBoard.init(PlayerBoard.GameBoard);
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Coloring
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

bool Player::isPlacementOver(bool ShouldReport)
{
	if (ShouldReport) 
	{
		cout << "Checking if " << Name << " has ships to place in the board....\n";
		Sleep(500);
		cout << "Seems like " << Name << " has:\n\n";
	}
	
	bool PlacmentOver = true;
	for (int i = 0; i < (sizeof(smallShips) / sizeof(smallShips[0])); i++)
	{
		if (smallShips[i].shipStatEnum == ShipStatEnum::Notdeployed) 
		{
			if (ShouldReport) cout << " small ship\n";
			PlacmentOver = false;
		}
	}
	for (int i = 0; i < (sizeof(mediumShips) / sizeof(mediumShips[0])); i++)
	{
		if (mediumShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
		{
			if (ShouldReport) cout << " medium ship v" << i <<"\n";
			PlacmentOver = false;
		}
	}
	for (int i = 0; i < (sizeof(largeShips) / sizeof(largeShips[0])); i++)
	{
		if (largeShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
		{
			if (ShouldReport) cout << " large ship\n";
			PlacmentOver = false;
		}
	}
	for (int i = 0; i < (sizeof(xlShips) / sizeof(xlShips[0])); i++)
	{
		if (xlShips[i].shipStatEnum == ShipStatEnum::Notdeployed) 
		{
			if (ShouldReport) cout << " xlarge ship\n";
			PlacmentOver = false;
		}
	}

	if (ShouldReport) 
	{
		cout << "\n";
		if(PlacmentOver) cout << "no ships to place\n\n";
		else cout << "remaining to place\n\n";
	}
	return PlacmentOver;
}

bool Player::IsShipFitInBoard(int x, int y, int size, ShipOriEnum shipOriEnum)
{
	bool FitInBoards = true;
	switch (shipOriEnum)
	{
	case ShipOriEnum::up:

		if (x - size < 0)
		{
			FitInBoards = false;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (PlayerBoard.GameBoard[x - i][y].nodeStatEnum != NodeStatEnum::empty)
			{
				FitInBoards = false;
				break;
			}
		}
		break;
	case ShipOriEnum::down:

		if (x + size >= BoardSize)
		{
			FitInBoards = false;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (PlayerBoard.GameBoard[x + i][y].nodeStatEnum != NodeStatEnum::empty)
			{
				FitInBoards = false;
				break;
			}
		}
		break;
	case ShipOriEnum::left:

		if (y - size < 0)
		{
			FitInBoards = false;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (PlayerBoard.GameBoard[x][y - i].nodeStatEnum != NodeStatEnum::empty)
			{
				FitInBoards = false;
				break;
			}
		}
		break;
	case ShipOriEnum::right:

		if (y + size >= BoardSize)
		{
			FitInBoards = false;
			break;
		}
		for (int i = 0; i < size; i++)
		{
			if (PlayerBoard.GameBoard[x][y + i].nodeStatEnum != NodeStatEnum::empty)
			{
				FitInBoards = false;
				break;
			}
		}
		break;
	}

	return FitInBoards;
}

int Player::RandomNumber(int max)
{
	int randNum = (rand() % max);

	return randNum;
}

void Player::HandlePlayerInput(Ship(&shipToPlace))
{
	system("cls");
	PlayerBoard.Draw(PlayerBoard.GameBoard, true);

	SetConsoleTextAttribute(hConsole, 10);
	cout << "         placing a ship in size " << shipToPlace.Size << "\n";
	SetConsoleTextAttribute(hConsole, 7);


	int x = -1;
	int y = -1;
	ShipOriEnum direction = ShipOriEnum::up;
	int input = -1;
	
		cout << "Please enter the X coordinate. (From 0 - 9) \n";

		cin >> input;
		// check if input is numeric and in the size and in the size of our grid.
		if (input >= 0 && input < BoardSize) 
		{
			x = (int)input;
			cout << "Great lets continue,\n";
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "YOU MADE A MISTAKE !!!!, \n";
			SetConsoleTextAttribute(hConsole, 7);
			cout << "Please try again... ^^ \n";
			system("pause");
			HandlePlayerInput(shipToPlace);
		}

		cout << "Please enter the Y coordinate. (From 0 - 9) \n";

		cin >> input;

		if (input >= 0 && input < BoardSize) 
		{
			y = (int)input;
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "YOU MADE A MISTAKE !!!!, \n";
			SetConsoleTextAttribute(hConsole, 7);
			cout << "Please try again... ^^ \n";
			system("pause");
			HandlePlayerInput(shipToPlace);
		}

		cout << "Please choose the direction to place the ship: (enter a number)\n";
		Sleep(100);
		cout << "0. up\n";
		Sleep(100);
		cout << "1. down\n";
		Sleep(100);
		cout << "2. left\n";
		Sleep(100);
		cout << "3. right\n";

		cin >> input;
		if (input >= 0 && input < 4)
		{
			switch (input)
			{
			case 0:
				direction = ShipOriEnum::up;
				break;
			case 1:
				direction = ShipOriEnum::down;
				break;
			case 2:
				direction = ShipOriEnum::left;
				break;
			case 3:
				direction = ShipOriEnum::right;
				break;
			}
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "YOU MADE A MISTAKE !!!!, \n";
			SetConsoleTextAttribute(hConsole, 7);
			cout << "Please try again... ^^ \n";
			system("pause");
			HandlePlayerInput(shipToPlace);
		}

		if (IsShipFitInBoard(x, y, shipToPlace.Size, direction)) 
		{
			placeShip(x, y, shipToPlace, direction, PlayerBoard.GameBoard);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 4);
			cout << "The ship does not fit inside the boards, \n";
			SetConsoleTextAttribute(hConsole, 7);
			cout << "Please try again... ^^ \n";
			system("pause");
			HandlePlayerInput(shipToPlace);
		}
}

void Player::ChooseShipToPlace()
{
	system("cls");
	PlayerBoard.Draw(PlayerBoard.GameBoard, true);
	int input = -1;
	char charInput = ' ';

	if (!isPlacementOver(true)) 
	{
		cout << "Please choose a ship to place \n";
		cout << "0. small ship \n";
		cout << "1. medium ship v0 \n";
		cout << "2. medium ship v1 \n";
		cout << "3. large ship\n";
		cout << "4. xlarge ship\n";

		cin >> input;

		if (input >= 0 && input < 5)
		{
			switch (input)
			{
				case 0:
					if (smallShips[0].shipStatEnum != ShipStatEnum::alive)
					{
					HandlePlayerInput(smallShips[0]);
					}
					else
					{
						cout << "This ship is already placed on the board, \n"; 
						Sleep(100);
						cout << "Do you want to REplace it? (Y / N) \n";
						cin >> charInput;
						if (charInput == 'Y')
						{
							smallShips[0].clear();
							PlayerBoard.Clear(PlayerBoard.GameBoard);
							RunOverShipsToRemark();
							PlayerBoard.Draw(PlayerBoard.GameBoard,true);
							HandlePlayerInput(smallShips[0]);
						}
						else
						{
							ChooseShipToPlace();
						}
						
					}
				break;
				case 1:
					if (mediumShips[0].shipStatEnum != ShipStatEnum::alive)
					{
						HandlePlayerInput(mediumShips[0]);
					}
					else
					{
						cout << "This ship is already placed on the board, \n";
						Sleep(100);
						cout << "Do you want to REplace it? (Y / N) \n";
						cin >> charInput;
						if (charInput == 'Y')
						{
							mediumShips[0].clear();
							RunOverShipsToRemark();
							PlayerBoard.Draw(PlayerBoard.GameBoard, true);
							HandlePlayerInput(mediumShips[0]);
						}
						else
						{
							ChooseShipToPlace();
						}

					}
					break;
				case 2:
					if (mediumShips[1].shipStatEnum != ShipStatEnum::alive)
					{
						HandlePlayerInput(mediumShips[1]);
					}
					else
					{
						cout << "This ship is already placed on the board, \n";
						Sleep(100);
						cout << "Do you want to REplace it? (Y / N) \n";
						cin >> charInput;
						if (charInput == 'Y')
						{
							mediumShips[1].clear();
							RunOverShipsToRemark();
							PlayerBoard.Draw(PlayerBoard.GameBoard, true);
							HandlePlayerInput(mediumShips[1]);
						}
						else
						{
							ChooseShipToPlace();
						}

					}
					break;
				case 3:
					if (largeShips[0].shipStatEnum != ShipStatEnum::alive)
					{
						HandlePlayerInput(largeShips[0]);
					}
					else
					{
						cout << "This ship is already placed on the board, \n";
						Sleep(100);
						cout << "Do you want to REplace it? (Y / N) \n";
						cin >> charInput;
						if (charInput == 'Y')
						{
							largeShips[0].clear();
							RunOverShipsToRemark();
							PlayerBoard.Draw(PlayerBoard.GameBoard, true);
							HandlePlayerInput(largeShips[0]);
						}
						else
						{
							ChooseShipToPlace();
						}

					}
					break;
				case 4:
					if (xlShips[0].shipStatEnum != ShipStatEnum::alive)
					{
						HandlePlayerInput(xlShips[0]);
					}
					else
					{
						cout << "This ship is already placed on the board, \n";
						Sleep(100);
						cout << "Do you want to REplace it? (Y / N) \n";
						cin >> input;
						if (input == 'Y')
						{
							xlShips[0].clear();
							RunOverShipsToRemark();
							PlayerBoard.Draw(PlayerBoard.GameBoard, true);
							HandlePlayerInput(xlShips[0]);
						}
						else
						{
							ChooseShipToPlace();
						}

					}
					break;
			}
		}
		else 
		{
			{
				SetConsoleTextAttribute(hConsole, 4);
				cout << "YOU MADE A MISTAKE !!!!, \n";
				SetConsoleTextAttribute(hConsole, 7);
				cout << "Please try again... ^^ \n";
				system("pause");
				ChooseShipToPlace();
			}
		}
	}
	else
	{
		cout << "you are done placing ships";
	}
}

void Player::PlaceShipRandomlly()
{
	{
		int randomX = RandomNumber(BoardSize);
		int randomY = RandomNumber(BoardSize);

		for (int i = 0; i < (sizeof(smallShips) / sizeof(smallShips[0])); i++)
		{
			if (smallShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
			{
				if (IsShipFitInBoard(randomX, randomY, smallShips[i].Size, ShipOriEnum::up))
				{
					placeShip(randomX, randomY, smallShips[i], ShipOriEnum::up, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, smallShips[i].Size, ShipOriEnum::down))
				{
					placeShip(randomX, randomY, smallShips[i], ShipOriEnum::down, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, smallShips[i].Size, ShipOriEnum::right))
				{
					placeShip(randomX, randomY, smallShips[i], ShipOriEnum::right, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, smallShips[i].Size, ShipOriEnum::left))
				{
					placeShip(randomX, randomY, smallShips[i], ShipOriEnum::left, PlayerBoard.GameBoard);
					return;
				}

			}
		}
		for (int i = 0; i < (sizeof(mediumShips) / sizeof(mediumShips[0])); i++)
		{
			if (mediumShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
			{
				if (IsShipFitInBoard(randomX, randomY, mediumShips[i].Size, ShipOriEnum::up))
				{
					placeShip(randomX, randomY, mediumShips[i], ShipOriEnum::up, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, mediumShips[i].Size, ShipOriEnum::down))
				{
					placeShip(randomX, randomY, mediumShips[i], ShipOriEnum::down, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, mediumShips[i].Size, ShipOriEnum::right))
				{
					placeShip(randomX, randomY, mediumShips[i], ShipOriEnum::right, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, mediumShips[i].Size, ShipOriEnum::left))
				{
					placeShip(randomX, randomY, mediumShips[i], ShipOriEnum::left, PlayerBoard.GameBoard);
					return;
				}
			}
		}
		for (int i = 0; i < (sizeof(largeShips) / sizeof(largeShips[0])); i++)
		{
			if (largeShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
			{
				if (IsShipFitInBoard(randomX, randomY, largeShips[i].Size, ShipOriEnum::up))
				{
					placeShip(randomX, randomY, largeShips[i], ShipOriEnum::up, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, largeShips[i].Size, ShipOriEnum::down))
				{
					placeShip(randomX, randomY, largeShips[i], ShipOriEnum::down, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, largeShips[i].Size, ShipOriEnum::right))
				{
					placeShip(randomX, randomY, largeShips[i], ShipOriEnum::right, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, largeShips[i].Size, ShipOriEnum::left))
				{
					placeShip(randomX, randomY, largeShips[i], ShipOriEnum::left, PlayerBoard.GameBoard);
					return;
				}

			}
		}
		for (int i = 0; i < (sizeof(xlShips) / sizeof(xlShips[0])); i++)
		{
			if (xlShips[i].shipStatEnum == ShipStatEnum::Notdeployed)
			{
				if (IsShipFitInBoard(randomX, randomY, xlShips[i].Size, ShipOriEnum::up))
				{
					placeShip(randomX, randomY, xlShips[i], ShipOriEnum::up, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, xlShips[i].Size, ShipOriEnum::down))
				{
					placeShip(randomX, randomY, xlShips[i], ShipOriEnum::down, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, xlShips[i].Size, ShipOriEnum::right))
				{
					placeShip(randomX, randomY, xlShips[i], ShipOriEnum::right, PlayerBoard.GameBoard);
					return;
				}
				if (IsShipFitInBoard(randomX, randomY, xlShips[i].Size, ShipOriEnum::left))
				{
					placeShip(randomX, randomY, xlShips[i], ShipOriEnum::left, PlayerBoard.GameBoard);
					return;
				}
			}
		}
		if (!isPlacementOver(false))
		{
			PlaceShipRandomlly();
		}
	}
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
	if (y + 1 < BoardSize && x + 1 <= BoardSize && gameBoard[x + 1][y + 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x + 1][y + 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y + 1 < BoardSize && x - 1 >= 0 && gameBoard[x - 1][y + 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x - 1][y + 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y - 1 >= 0 && x + 1 <= BoardSize && gameBoard[x + 1][y - 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x + 1][y - 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y + 1 < BoardSize && gameBoard[x][y + 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x][y + 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
	if (y - 1 >= 0 && gameBoard[x][y - 1].nodeStatEnum != NodeStatEnum::ocupied)
	{
		gameBoard[x][y - 1].nodeStatEnum = NodeStatEnum::unplacable;
	}
}

void Player::MarkAttempted(Ship(&shipToMarkAround), Node(&gameBoard)[BoardSize][BoardSize])
{
	for (int i = 0; i < shipToMarkAround.Size ; i++)
	{
		int x = shipToMarkAround.ShipNodes[i].X;
		int y = shipToMarkAround.ShipNodes[i].Y;

		if (x - 1 >= 0 && gameBoard[x - 1][y].nodeStatEnum != NodeStatEnum::hit)
		{
			gameBoard[x - 1][y].nodeStatEnum = NodeStatEnum::attempted;
		}
		if (x + 1 <= BoardSize && gameBoard[x + 1][y].nodeStatEnum != NodeStatEnum::hit)
		{
			gameBoard[x + 1][y].nodeStatEnum = NodeStatEnum::attempted;
		}
		if (y - 1 >= 0 && x - 1 >= 0 && gameBoard[x - 1][y - 1].nodeStatEnum != NodeStatEnum::hit)
		{
			gameBoard[x - 1][y - 1].nodeStatEnum = NodeStatEnum::attempted;
		}
		if (y + 1 < BoardSize && x + 1 <= BoardSize && gameBoard[x + 1][y + 1].nodeStatEnum != NodeStatEnum::hit)
		{
			gameBoard[x + 1][y + 1].nodeStatEnum = NodeStatEnum::attempted;
		}
		if (y + 1 < BoardSize && x - 1 >= 0 && gameBoard[x - 1][y + 1].nodeStatEnum != NodeStatEnum::hit)
		{
			gameBoard[x - 1][y + 1].nodeStatEnum = NodeStatEnum::attempted;
		}
		if (y - 1 >= 0 && x + 1 <= BoardSize && gameBoard[x + 1][y - 1].nodeStatEnum != NodeStatEnum::hit)
		{
			gameBoard[x + 1][y - 1].nodeStatEnum = NodeStatEnum::attempted;
		}
		if (y + 1 < BoardSize && gameBoard[x][y + 1].nodeStatEnum != NodeStatEnum::hit)
		{
			gameBoard[x][y + 1].nodeStatEnum = NodeStatEnum::attempted;
		}
		if (y - 1 >= 0 && gameBoard[x][y - 1].nodeStatEnum != NodeStatEnum::hit)
		{
			gameBoard[x][y - 1].nodeStatEnum = NodeStatEnum::attempted;
		}
	}
}

void Player::RunOverShipsToRemark()
{
	for (int i = 0; i < (sizeof(smallShips) / sizeof(smallShips[0])); i++)
	{
		if (smallShips[i].shipStatEnum == ShipStatEnum::alive) 
		{
			for (int j = 0; j < (sizeof(smallShips[i].ShipNodes) / sizeof(smallShips[i].ShipNodes[0])); i++)
			{
				MarkUnplacable(smallShips[i].ShipNodes[j].X, smallShips[i].ShipNodes[j].Y, PlayerBoard.GameBoard);
			}
		}
	}
	for (int i = 0; i < (sizeof(mediumShips) / sizeof(mediumShips[0])); i++)
	{
		if (mediumShips[i].shipStatEnum == ShipStatEnum::alive) 
		{
			for (int j = 0; j < (sizeof(mediumShips[i].ShipNodes) / sizeof(mediumShips[i].ShipNodes[0])); i++)
			{
				MarkUnplacable(mediumShips[i].ShipNodes[j].X, mediumShips[i].ShipNodes[j].Y, PlayerBoard.GameBoard);
			}
		}
	}
	for (int i = 0; i < (sizeof(largeShips) / sizeof(largeShips[0])); i++)
	{
		if (largeShips[i].shipStatEnum == ShipStatEnum::alive)
		{
			for (int j = 0; j < (sizeof(largeShips[i].ShipNodes) / sizeof(largeShips[i].ShipNodes[0])); i++)
			{
				MarkUnplacable(largeShips[i].ShipNodes[j].X, largeShips[i].ShipNodes[j].Y, PlayerBoard.GameBoard);
			}
		}
	}
	for (int i = 0; i < (sizeof(xlShips) / sizeof(xlShips[0])); i++)
	{
		if (xlShips[i].shipStatEnum == ShipStatEnum::alive)
		{
			for (int j = 0; j < (sizeof(xlShips[i].ShipNodes) / sizeof(xlShips[i].ShipNodes[0])); i++)
			{
				MarkUnplacable(xlShips[i].ShipNodes[j].X, xlShips[i].ShipNodes[j].Y, PlayerBoard.GameBoard);
			}
		}
	}
}

void Player::GuessPointOnBoard(Node(&gameBoard)[BoardSize][BoardSize], Player(&otherPlayer))
{
	int randomX = RandomNumber(BoardSize);
	int randomY = RandomNumber(BoardSize);
	switch (gameBoard[randomX][randomY].nodeStatEnum)
	{
	case NodeStatEnum::attempted:
		GuessPointOnBoard(gameBoard, otherPlayer);
		break;
	case NodeStatEnum::hit:
		GuessPointOnBoard(gameBoard, otherPlayer);
		break;
	case NodeStatEnum::empty:
		gameBoard[randomX][randomY].nodeStatEnum = NodeStatEnum::attempted;
		shouldPlayAgain = false;
				SetConsoleTextAttribute(hConsole, 15);
		cout << Name << " Has hit an empty node" << " X " << randomX << " Y " << randomY <<"\n";
				SetConsoleTextAttribute(hConsole, 7);
		break;
	case NodeStatEnum::unplacable:
				SetConsoleTextAttribute(hConsole, 15);
		cout << Name << " Has hit an empty node" << " X " << randomX << " Y " << randomY <<"\n";
				SetConsoleTextAttribute(hConsole, 7);
		gameBoard[randomX][randomY].nodeStatEnum = NodeStatEnum::attempted;
		shouldPlayAgain = false;
		break;
	case NodeStatEnum::ocupied: //HIT!
		gameBoard[randomX][randomY].nodeStatEnum = NodeStatEnum::hit;
		HandleHit(randomX, randomY, gameBoard, otherPlayer);
		shouldPlayAgain = true;
		break;
	default:
		break;
	}

}

void Player::ChooseNodeToHit(Player(&otherPlayer))
{

	int x = -1;
	int y = -1;
	int input = -1;

	cout << "Please enter the X coordinate. (From 0 - 9) \n";

	cin >> input;
	if (input >= 0 && input < BoardSize)
	{
		x = (int)input;
		cout << "Great lets continue,\n";
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 4);
		cout << "YOU MADE A MISTAKE !!!!, \n";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Please try again... ^^ \n";
		system("pause");
	}

	cout << "Please enter the Y coordinate. (From 0 - 9) \n";

	cin >> input;

	if (input >= 0 && input < BoardSize)
	{
		y = (int)input;
	}
	else
	{
		SetConsoleTextAttribute(hConsole, 4);
		cout << "YOU MADE A MISTAKE !!!!, \n";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Please try again... ^^ \n";
		system("pause");
	}
	switch (otherPlayer.PlayerBoard.GameBoard[x][y].nodeStatEnum)
	{
	case NodeStatEnum::attempted:
	case NodeStatEnum::hit:
		SetConsoleTextAttribute(hConsole, 4);
		cout << "YOU ALREADY BOMBED THIS NODE !!!!, \n";
		SetConsoleTextAttribute(hConsole, 7);
		cout << "Please try again... ^^ \n";
		ChooseNodeToHit(otherPlayer);
		break;
	case NodeStatEnum::empty:
		otherPlayer.PlayerBoard.GameBoard[x][y].nodeStatEnum = NodeStatEnum::attempted;
		shouldPlayAgain = false;
		SetConsoleTextAttribute(hConsole, 15);
		cout <<Name << " Has hit an empty node" << " X " << x << " Y " << y << "\n";
		SetConsoleTextAttribute(hConsole, 7);
		break;
	case NodeStatEnum::unplacable:
		SetConsoleTextAttribute(hConsole, 15);
		cout << Name << " Has hit an empty node" << " X " << x << " Y " << y << "\n";
		SetConsoleTextAttribute(hConsole, 7);
		otherPlayer.PlayerBoard.GameBoard[x][y].nodeStatEnum = NodeStatEnum::attempted;
		shouldPlayAgain = false;
		break;
	case NodeStatEnum::ocupied: //HIT!
		otherPlayer.PlayerBoard.GameBoard[x][y].nodeStatEnum = NodeStatEnum::hit;
		HandleHit(x, y, otherPlayer.PlayerBoard.GameBoard, otherPlayer);
		shouldPlayAgain = true;
		break;
	default:
		break;
	}

}

void Player::HandleHit(int x, int y, Node(&gameBoard)[BoardSize][BoardSize], Player(&otherPlayer))
{
	for (int i = 0; i < (sizeof(smallShips) / sizeof(smallShips[0])); i++)
	{
		if (otherPlayer.smallShips[i].IsHitOnThisShip(x, y))
		{
			if (otherPlayer.smallShips[i].IsAlive())
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << Name << " Has hit a ship" << " X " << x << " Y " << y << "\n";
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 14);
				cout <<Name << " Has destroyed a size "  << otherPlayer.smallShips[i].Size <<" ship" << "\n";
				SetConsoleTextAttribute(hConsole, 7);
				MarkAttempted(otherPlayer.smallShips[i], gameBoard);
			}
		}
	}
	for (int i = 0; i < (sizeof(mediumShips) / sizeof(mediumShips[0])); i++)
	{
		if (otherPlayer.mediumShips[i].IsHitOnThisShip(x, y))
		{
			if (otherPlayer.mediumShips[i].IsAlive())
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << Name << " Has hit a ship" << " X " << x << " Y " << y << "\n";
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 14);
				cout << Name << " Has destroyed a size " << otherPlayer.mediumShips[i].Size << " ship" << "\n";
				MarkAttempted(otherPlayer.mediumShips[i], gameBoard);
				SetConsoleTextAttribute(hConsole, 7);
			}
		}
	}
	for (int i = 0; i < (sizeof(largeShips) / sizeof(largeShips[0])); i++)
	{
		if (otherPlayer.largeShips[i].IsHitOnThisShip(x, y))
		{
			if (otherPlayer.largeShips[i].IsAlive())
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << Name << " Has hit a ship" << " X " << x << " Y " << y << "\n";
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 14);
				cout << Name << " Has destroyed a size " << otherPlayer.largeShips[i].Size << " ship" << "\n";
				MarkAttempted(otherPlayer.largeShips[i], gameBoard);
			}
				SetConsoleTextAttribute(hConsole, 7);
		}
	}
	for (int i = 0; i < (sizeof(xlShips) / sizeof(xlShips[0])); i++)
	{
		if (otherPlayer.xlShips[i].IsHitOnThisShip(x, y))
		{
			if (otherPlayer.xlShips[i].IsAlive())
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << Name << " Has hit a ship" << " X " << x << " Y " << y << "\n";
				SetConsoleTextAttribute(hConsole, 7);
				break;
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 14);
				cout << Name << " Has destroyed a size " << otherPlayer.xlShips[i].Size << " ship" << "\n";
				MarkAttempted(otherPlayer.xlShips[i], gameBoard);
			}
				SetConsoleTextAttribute(hConsole, 7);
		}
	}


 }


