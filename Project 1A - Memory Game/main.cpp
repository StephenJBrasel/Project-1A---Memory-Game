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

void Simon(DynArray<char> * thing);
void DisplayHighScores(DynArray<char> * thing);
////////////////////////////////////////////////////////////////////////////////////////////////
// Function :	main
// Parameters : argc - the number of command line arguments
//				argv - the array of command line arguments
// return :		int - 0 for success
////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char ** argv)
{
	DynArray<char> * chars = new DynArray<char>();
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
		while (!restart && !exit)
		{
			exit = false;
			restart = false;
			if (_kbhit())
			{
				char ch = _getch();
				switch (tolower(ch))
				{
				case '1':
					Simon(chars);
					restart = true;
					break;
				case '2':
					DisplayHighScores(chars);
					restart = true;
					break;
				case '3':
					exit = true;
					break;
				default:
					break;
				}
			}
		}
	}
	// complete.
	return 0;
}
void Simon(DynArray<char> * thing)
{

	empty();
	while (true)
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
				empty();
			}
			break;

			case 's':
			{
				drawDown();
				delay(150);
				empty();
			}
			break;

			case 'a':
			{
				drawLeft();
				delay(150);
				empty();
			}
			break;

			case 'd':
			{
				drawRight();
				delay(150);
				empty();
			}
			break;
			}

			// exit on the 'q' key
			if (ch == 'q')
				break;
		}
	}
}

void DisplayHighScores(DynArray<char> * thing)
{
	for (int i = 0; i < thing->size(); i++)
	{

	}
}