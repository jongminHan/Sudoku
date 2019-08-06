#include "Sudoku.h"

int GenerateRandNum(int maxLimit)
{
	return rand() % maxLimit;
}

Sudoku::Sudoku()
	: mDifficultyLevel(0)  // Initialize difficulty level
{
	// Randomly shuffling the array of removing grid positions
	for (int i = 0; i < 81; i++)
	{
		mGridPos[i] = i;
	}

	std::random_shuffle(mGridPos, mGridPos + 81, GenerateRandNum);

	// Randomly shuffling the guessing number array
	for (int i = 0; i < 9; i++)
	{
		mGuessNum[i] = i + 1;
	}

	std::random_shuffle(mGuessNum, mGuessNum + 9, GenerateRandNum);

	// Initializing the grid
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mGrid[i][j] = 0;
		}
	}
}

void Sudoku::CreateSeed()
{
	SolveGrid();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mSolnGrid[i][j] = mGrid[i][j];
		}
	}
}

void Sudoku::PrintGrid()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (mGrid[i][j] == 0)
			{
				std::cout << ".";
			}
			else
			{
				std::cout << mGrid[i][j];
			}
			std::cout << "|";
		}
		std::cout << std::endl;
	}

	std::cout << "\nDifficulty of current sudoku(0 being easiest): " << mDifficultyLevel << std::endl;
}

bool Sudoku::SolveGrid() // Sudoku solver
{
	int row;
	int col;

	// If there is no unassigned location, we are done
	if (!FindUnassignedLocation(mGrid, row, col))
	{
		return true; // Success!
	}

	// Consider digits 1 to 9
	for (int num = 0; num < 9; num++)
	{
		// If looks promising
		if (IsSafe(mGrid, row, col, mGuessNum[num]))
		{
			// Make tentative assignment
			mGrid[row][col] = mGuessNum[num];

			// Return, if success, yay!
			if (SolveGrid())
			{
				return true;
			}

			// Failure, unmake & try again
			mGrid[row][col] = UNASSIGNED;
		}
	}

	return false;  // This triggers backtracking
}

void Sudoku::CountSoln(int& number)
{
	int row;
	int col;

	if (!FindUnassignedLocation(mGrid, row, col))
	{
		number++;
		return;
	}

	for (int i = 0; i < 9 && number < 2; i++)
	{
		if (IsSafe(mGrid, row, col, mGuessNum[i]))
		{
			mGrid[row][col] = mGuessNum[i];
			CountSoln(number);
		}

		mGrid[row][col] = UNASSIGNED;
	}
}

void Sudoku::GenPuzzle()
{
	for (int i = 0; i < 81; i++)
	{
		int x = mGridPos[i] / 9;
		int y = mGridPos[i] % 9;
		int temp = mGrid[x][y];
		mGrid[x][y] = UNASSIGNED;


	}
}
