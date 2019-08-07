#include "Sudoku.h"

// START: Generate random number
int genRandNum(int maxLimit)
{
	return rand() % maxLimit;
}
// END: Generate random number


// START: Create seed mGrid
void Sudoku::CreateSeed()
{
	SolveGrid();

	// Saving the solution mGrid
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mSolnGrid[i][j] = mGrid[i][j];
		}
	}
}
// END: Create seed mGrid


// START: Intialising
Sudoku::Sudoku()
{

	// initialize difficulty level
	mDifficultyLevel = 0;

	// Randomly shuffling the array of removing mGrid positions
	for (int i = 0; i < 81; i++)
	{
		mGridPos[i] = i;
	}

	std::random_shuffle(mGridPos, (mGridPos)+81, genRandNum);

	// Randomly shuffling the guessing number array
	for (int i = 0; i < 9; i++)
	{
		mGuessNum[i] = i + 1;
	}

	std::random_shuffle(mGuessNum, (mGuessNum)+9, genRandNum);

	// Initialising the mGrid
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mGrid[i][j] = 0;
		}
	}

}
// END: Initialising


// START: Printing the mGrid
void Sudoku::PrintGrid()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (mGrid[i][j] == 0)
				std::cout << ".";
			else
				std::cout << mGrid[i][j];
			std::cout << "|";
		}
		std::cout << std::endl;
	}

	std::cout << "\nDifficulty of current sudoku(0 being easiest): " << mDifficultyLevel;
	std::cout << std::endl;
}
// END: Printing the mGrid


// START: Helper functions for solving mGrid
bool FindUnassignedLocation(int grid[9][9], int &row, int &col)
{
	for (row = 0; row < 9; row++)
	{
		for (col = 0; col < 9; col++)
		{
			if (grid[row][col] == UNASSIGNED)
				return true;
		}
	}

	return false;
}

bool UsedInRow(int grid[9][9], int row, int num)
{
	for (int col = 0; col < 9; col++)
	{
		if (grid[row][col] == num)
			return true;
	}

	return false;
}

bool UsedInCol(int grid[9][9], int col, int num)
{
	for (int row = 0; row < 9; row++)
	{
		if (grid[row][col] == num)
			return true;
	}

	return false;
}

bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (grid[row + boxStartRow][col + boxStartCol] == num)
				return true;
		}
	}

	return false;
}

bool isSafe(int grid[9][9], int row, int col, int num)
{
	return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row % 3, col - col % 3, num);
}

// END: Helper functions for solving mGrid


// START: Modified and improved Sudoku solver
bool Sudoku::SolveGrid()
{
	int row, col;

	// If there is no unassigned location, we are done
	if (!FindUnassignedLocation(mGrid, row, col))
		return true; // success!

	   // Consider digits 1 to 9
	for (int num = 0; num < 9; num++)
	{
		// if looks promising
		if (isSafe(mGrid, row, col, mGuessNum[num]))
		{
			// make tentative assignment
			mGrid[row][col] = mGuessNum[num];

			// return, if success, yay!
			if (SolveGrid())
				return true;

			// failure, unmake & try again
			mGrid[row][col] = UNASSIGNED;
		}
	}

	return false; // this triggers backtracking

}
// END: Modified and improved Sudoku Solver


// START: Check if the mGrid is uniquely solvable
void Sudoku::CountSoln(int& number)
{
	int row, col;

	if (!FindUnassignedLocation(mGrid, row, col))
	{
		number++;
		return;
	}


	for (int i = 0; i < 9 && number < 2; i++)
	{
		if (isSafe(mGrid, row, col, mGuessNum[i]))
		{
			mGrid[row][col] = mGuessNum[i];
			CountSoln(number);
		}

		mGrid[row][col] = UNASSIGNED;
	}

}
// END: Check if the mGrid is uniquely solvable


// START: Gneerate puzzle
void Sudoku::GenPuzzle()
{
	for (int i = 0; i < 81; i++)
	{
		int x = (mGridPos[i]) / 9;
		int y = (mGridPos[i]) % 9;
		int temp = mGrid[x][y];
		mGrid[x][y] = UNASSIGNED;

		// If now more than 1 solution , replace the removed cell back.
		int check = 0;
		CountSoln(check);
		if (check != 1)
		{
			mGrid[x][y] = temp;
		}
	}
}
// END: Generate puzzle

// START: Calculate branch difficulty score
int Sudoku::BranchDifficultyScore()
{
	int emptyPositions = -1;
	int tempGrid[9][9];
	int sum = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			tempGrid[i][j] = mGrid[i][j];
		}
	}

	while (emptyPositions != 0)
	{
		std::vector<std::vector<int> > empty;

		for (int i = 0; i < 81; i++)
		{
			if (tempGrid[(int)(i / 9)][(int)(i % 9)] == 0)
			{
				std::vector<int> temp;
				temp.push_back(i);

				for (int num = 1; num <= 9; num++)
				{
					if (isSafe(tempGrid, i / 9, i % 9, num))
					{
						temp.push_back(num);
					}
				}

				empty.push_back(temp);
			}

		}

		if (empty.size() == 0)
		{
			std::cout << "Hello: " << sum << std::endl;
			return sum;
		}

		int minIndex = 0;

		int check = empty.size();
		for (int i = 0; i < check; i++)
		{
			if (empty[i].size() < empty[minIndex].size())
				minIndex = i;
		}

		int branchFactor = empty[minIndex].size();
		int rowIndex = empty[minIndex][0] / 9;
		int colIndex = empty[minIndex][0] % 9;

		tempGrid[rowIndex][colIndex] = mSolnGrid[rowIndex][colIndex];
		sum = sum + ((branchFactor - 2) * (branchFactor - 2));

		emptyPositions = empty.size() - 1;
	}

	return sum;

}
// END: Finish branch difficulty score


// START: Calculate difficulty level of current mGrid
void Sudoku::CalculateDifficulty()
{
	int B = BranchDifficultyScore();
	int emptyCells = 0;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (mGrid[i][j] == 0)
				emptyCells++;
		}
	}

	mDifficultyLevel = B * 100 + emptyCells;
}
// END: calculating difficulty level