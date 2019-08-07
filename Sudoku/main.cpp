#include "Sudoku.h"

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

	// Calculating difficulty of puzzle
	puzzle->CalculateDifficulty();

	// testing by printing the mGrid
	puzzle->PrintGrid();

	delete puzzle;

	return 0;
}
// END: The main function