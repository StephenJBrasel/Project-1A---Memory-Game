////////////////////////////////////////////////////////////////////////////////////////////////
// File :			main.cpp
// Author :			Rodney Stoeffler
// Created :		03.24.08
// Last Modified :	10.29.09
// Purpose :		The main driver for the memory game
// Notes :			Property of Full Sail University, Data Structures Course.
////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////
// INCLUDES
////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>				// needed for drawing the screen
#include <conio.h>				// needed for _kbhit and _getch.
#include "MemoryFunctions.h"	// interface for drawing the screen and delay function
#include "DynArray.h"			// needed for DynArrays. 
#include <random>				// NEEDED FOR RANDONIMITY


using namespace std;

struct Player
{
private:
	int score = 0;
	char* name = nullptr;
public:
	//Accessors
	int const GetScore() const { return score; }
	char const * const GetName() const { return name; }
	//Mutators
	void IncrementScore() { score++; }
	void SetName()
	{
		char * temp = new char[32];
		cin.clear();
		cin.ignore();
		cin.getline(temp, 32);

		delete[] name;
		name = _strdup(temp);
		delete[] temp;
	}
};

void Simon();
void DisplayHighScores(DynArray<Player> thing);
void Check(char ch, DynArray<char> * chars, unsigned int &increment, bool &memorized);
////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
	DynArray<Player> * players = new DynArray<Player>();
	bool restart = false;
	bool exit = false;

	while (!exit)
	{
		exit = false;
		restart = false;

		cout << "Welcome to Simon. \n"
			<< "\n\n\n"
			<< "1) Play. \n"
			<< "2) View High Scores. \n"
			<< "3) Exit. \n";
		while (!restart)
		{
			exit = false;
			restart = false;
			if (_kbhit())
			{
				char ch = _getch();
				switch (tolower(ch))
				{
				case '1':
					Simon();
					system("cls");
					restart = true;
					break;
				case '2':
					system("cls");
					DisplayHighScores(*players);
					system("cls");
					restart = true;
					break;
				case '3':
					restart = true;
					exit = true;
					break;
				default:
					break;
				}
			}
		}
	}
	// complete.
	delete players;
	return 0;
}
void Check(char ch, DynArray<char> * chars, unsigned int &increment, bool &memorized)
{
	delay(150);
	if (tolower(ch) != (*chars)[increment])
		memorized = false;
	else
		increment++;
	empty();
}
void Simon(DynArray<char> * thing)
{
	DynArray<char> * chars = new DynArray<char>();
	unsigned srand();
	unsigned int increment = 0;
	bool memorized = true;
	while (memorized)
	{
		int temp = rand() % 4;
		switch (temp)
		{
		case 0:
			chars->append('w');
			break;
		case 1:
			chars->append('a');
			break;
		case 2:
			chars->append('s');
			break;
		case 3:
			chars->append('d');
			break;
		default:
			break;
		}
		empty();
		for (unsigned int i = 0; i < chars->size(); i++)
		{
			switch ((*chars)[i])
			{
			case 'w':
				drawUp();
				delay(150);
				empty();
				break;
			case 'a':
				drawLeft();
				delay(150);
				empty();
				break;
			case 's':
				drawDown();
				delay(150);
				empty();
				break;
			case 'd':
				drawRight();
				delay(150);
				empty();
				break;
			default:
				break;
			}
		}
		empty();
		increment = 0;
		while (memorized)
		{
			if (_kbhit())
			{
				char ch = _getch();
				switch (tolower(ch))
				{
					// show stuff for each specific move
				case 'w':
				{
					drawUp();
					Check(ch, chars, increment, memorized);
				}
				break;

				case 's':
				{
					drawDown();
					Check(ch, chars, increment, memorized);
				}
				break;

				case 'a':
				{
					drawLeft();
					Check(ch, chars, increment, memorized);
				}
				break;

				case 'd':
				{
					drawRight(); 
					Check(ch, chars, increment, memorized);
				}
				break;
				}

				// exit on the 'q' key
				if (ch == 'q')
					break;
			}
		}
	}

	delete chars;
}

void DisplayHighScores(DynArray<Player> thing)
{
	for (int i = 0; i < thing.size(); i++)
	{
		cout << thing[i].GetName() << "\t" << thing[i].GetScore() << "\n";
	}
}