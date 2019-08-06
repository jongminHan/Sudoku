#pragma once
#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#define UNASSIGNED 0

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
private:
	int mGrid[9][9];
	int mSolnGrid[9][9];
	int mGuessNum[9];
	int mGridPos[81];
	int mDifficultyLevel;
};