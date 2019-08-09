#include "Game.h"

int main()
{
	// Create the game object
	Game* game = new Game();

	// Initialize and run the game
	if (game->Init())
	{
		game->Run();
	}

	// Clean up
	delete game;
	return 0;
}

/*
// START: The main function
int main(int argc, char const *argv[])
{
	// Initialising seed for random number generation
	srand(static_cast<unsigned int>(time(nullptr)));

	// Creating an instance of Sudoku
	Sudoku* puzzle = new Sudoku();

	// Creating a seed for puzzle generation
	puzzle->CreateSeed();

	// Generating the puzzle
	puzzle->GenPuzzle();

	// testing by printing the mGrid
	puzzle->PrintGrid();

	delete puzzle;

	return 0;
}
// END: The main function
*/