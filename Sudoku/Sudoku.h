#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


int GenRandNum(int maxLimit);
bool UsedInRow(int grid[9][9], int row, int num);
bool UsedInCol(int grid[9][9], int col, int num);
bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num);
bool IsSafe(int grid[9][9], int row, int col, int num);


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
	bool FindUnassignedLocation(int grid[9][9], int& row, int& col);
private:
	static const int UNASSIGNED = 0;
	int mGrid[9][9];
	int mSolnGrid[9][9];
	int mGuessNum[9];
	int mGridPos[81];
};


