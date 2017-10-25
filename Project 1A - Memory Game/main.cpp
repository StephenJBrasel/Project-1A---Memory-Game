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
#include <crtdbg.h>				// Needed for memory leak detection


using namespace std;
////Also need this for memory leak code stuff
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//_CrtSetBreakAlloc(-1); //Important!

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
void EndScreen(DynArray<char> * thing);
void DisplayHighScores(DynArray<Player> thing);
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
					delay(300);
					Simon();
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
void Simon()
{
	DynArray<char> * chars = new DynArray<char>();
	//unsigned srand();
	unsigned int increment = 0;
	bool memorized = true;
	bool userGotAllChars = true;
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
		userGotAllChars = false;
		while (memorized && !userGotAllChars)
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
					delay(150);
					if (tolower(ch) != (*chars)[increment])
						memorized = false;
					else
						increment++;
					empty();
				}
				break;

				case 's':
				{
					drawDown();
					delay(150);
					if (tolower(ch) != (*chars)[increment])
						memorized = false;
					else
						increment++;
					empty();
				}
				break;

				case 'a':
				{
					drawLeft();
					delay(150);
					if (tolower(ch) != (*chars)[increment])
						memorized = false;
					else
						increment++;
					empty();
				}
				break;

				case 'd':
				{
					drawRight();
					delay(150);
					if (tolower(ch) != (*chars)[increment])
						memorized = false;
					else
						increment++;
					empty();
				}
				break;
				}

				// exit on the 'q' key
				if (ch == 'q')
				{
					memorized = false;
					break;
				}
				if (increment == chars->size())
					userGotAllChars = true;
			}
		}
	}
	system("cls");
	EndScreen(chars);
	delete chars;
}

void EndScreen(DynArray<char> * thing)
{
	int temp = thing->size();
	cout << "You got " << temp << " correct!\n";

	if (temp < 5)
		cout << "Better luck next time!\n";
	else if (temp >= 5 && temp < 15)
		cout << "That's great! Keep up the good work!\n";
	else if (temp >= 15 && temp < 10000)
		cout << "You're amazing! Clearly, the practice has paid off. \n";
	else
		cout << "Mnemosyne, as always, it's an honor to have you play my game.\n";

	delay(2000);
	system("cls");
}

void DisplayHighScores(DynArray<Player> thing)
{
	for (unsigned int i = 0; i < thing.size(); i++)
	{
		cout << thing[i].GetName() << "\t" << thing[i].GetScore() << "\n";
	}
}