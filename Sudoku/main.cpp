#include "Sudoku.h"

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	Sudoku* puzzle = new Sudoku();

	puzzle->CreateSeed();
	puzzle->GenPuzzle();
	puzzle->CalculateDifficulty();
	puzzle->PrintGrid();
	delete puzzle;
	return 0;
}