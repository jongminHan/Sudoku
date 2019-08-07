#pragma once
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Sudoku
{
public:
	Sudoku();
	virtual ~Sudoku() = default;
	void CreateSeed();
	void PrintGrid();
	bool SolveGrid();
	void CountSoln(int& number);
	void GenPuzzle();
	void CalculateDifficulty();
	int BranchDifficultyScore();
	bool FindUnassignedLocation(int grid[9][9], int& row, int& col);
	bool IsSafe(int grid[9][9], int row, int col, int num);
private:
	const static int UNASSIGNED = 0;
	int mGrid[9][9];
	int mSolnGrid[9][9];
	int mGuessNum[9];
	int mGridPos[81];
	int mDifficultyLevel;
};