/* GoldFinder.cpp
 * INFO 450
 * 2/17/2018
 * Program Description:
 * * Presents a game board and populates it with alluring and explosive loot.
 * * The player gets five tries to accumulate gold or get exploded by a bomb.
 */
#include "stdafx.h"
#include <iostream>
#include <time.h>
using namespace std;

//Game board dimensions
const int WIDTH = 8;
const int HEIGHT = 8;

void displayIntro();
void setBoard(char grid[WIDTH][HEIGHT], bool blank);
void buryLoot(char grid[WIDTH][HEIGHT], char loot, int amount);
int randomize(int range);
void playGame(char grid[WIDTH][HEIGHT], int tries);

int main()
{
	char board[WIDTH][HEIGHT], response; //board = array of game board squares
	bool blank = true;
	do //Loop of the whole game
	{ 
		displayIntro();
		setBoard(board, blank);
		buryLoot(board, 'G', 5);
		buryLoot(board, 'B', 1);
		playGame(board, 5); //5-turn gameplay, then end-game message
		setBoard(board, !blank); //Game board revealed
		cout << "\nWant to play again? Enter 'Y': ";
		cin >> response;
	} while (response == 'y' || response == 'Y');
	return 0;
}

//Welcome message
void displayIntro()
{
	cout << " *****************************************\n";
	cout << " **         G O L D F I N D E R         **\n";
	cout << " **  *********************************  **\n";
	cout << " **  There are 5 buried pieces of Gold  **\n";
	cout << " **    + 1 Bomb that can end the run    **\n";
	cout << " **  *********************************  **\n";
	cout << " **     How much Gold can you find?     **\n";
	cout << " **          You have 5 tries!          **\n";
	cout << " *****************************************\n\n";
}

//Initializes the blank array, and prints the board in its start or end state.
void setBoard(char grid[WIDTH][HEIGHT], bool blank)
{
	int row, col;
	cout << "     "; //Printing game board header...
	for (col = 0; col < WIDTH; col++)
	{
		cout << col + 1 << "  ";
	}
	cout << "\n    ";
	for (col = 0; col < WIDTH; col++)
	{
		cout << "___";
	} //...End game board header
	if (blank) //For initializing and printing the initial board
	{
		for (row = 0; row < HEIGHT; row++)
		{
			cout << endl << row + 1 << " |  ";
			for (col = 0; col < WIDTH; col++)
			{
				grid[col][row] = ' '; //Sets or resets element values to " "
				cout << "?  "; //Prints "?", not the element value
			}
		}
	}
	else //For printing post-gameplay board
	{
		for (row = 0; row < HEIGHT; row++)
		{
			cout << endl << row + 1 << " |  ";
			for (col = 0; col < WIDTH; col++)
			{
				cout << grid[col][row] << "  "; //Prints element value
			}
		}
	}
	cout << endl;
}

//Function assigns a char value ('loot') to a random unassigned element,
//repeating for an 'amount' of unique assignments.
void buryLoot(char grid[WIDTH][HEIGHT], char loot, int amount)
{
	int randCol, randRow;

	for (int i = 0; i < amount; i++)
	{
		do //Selects a random coordinate and ensures it was not yet assigned
		{
			randRow = randomize(HEIGHT);
			randCol = randomize(WIDTH);
		} while (grid[randCol][randRow] != ' ');
		grid[randCol][randRow] = loot;
		//cout << loot << i << "(" << randCol+1 << ", " << randRow+1 << ")\n";
			//I kept this behind a comment just for testing random int seeding
	}
}

//Gets and decrements player guesses, awards points, prints game-over message.
void playGame(char grid[WIDTH][HEIGHT], int tries)
{
	int row, col;
	int points = 0;
	while (tries > 0) //Loop of player's attempts until tries run out
	{
		cout << "\nYou have " << tries << " tries left.\n\nEnter column: ";
		cin >> col;
		cout << "Enter row: ";
		cin >> row;
		if (grid[(col - 1) % WIDTH][(row - 1) % WIDTH] == 'G')
		{
			cout << "You struck Gold! Cha-ching! Plus you get an extra turn.";
			grid[(col - 1) % WIDTH][(row - 1) % WIDTH] = 'F'; //Marks it found
			points++;
			//No change to the 'tries' countdown-counter means an extra turn
		}
		else if (grid[(col - 1) % WIDTH][(row - 1) % WIDTH] == 'B')
		{
			cout << "Boom it's a Bomb :(";
			tries = 0;
		}
		else
		{
			cout << "Miss! No joy.";
			tries--;
		}
	}
	cout << "\n\n *****************************************";
	cout << "\n **          G A M E   O V E R          **";
	cout << "\n **  *********************************  **";
	cout << "\n **         Your final score is         **";
	cout << "\n **              " << points << " POINTS               **";
	cout << "\n **  *********************************  **";
	cout << "\n **           Real good going           **";
	cout << "\n **      View the game board below      **";
	cout << "\n *****************************************\n\n";
}

//Generates a random integer within a set range. Used in buryLoot.
int randomize(int range)
{
	static int check = 0;
	if (check == 0)
	{
		srand(time(NULL));
	}
	check++;
	return rand() % range;
}