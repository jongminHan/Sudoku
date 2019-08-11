#pragma once
#include <TGUI/TGUI.hpp>
#include "Sudoku.h"
#include "HelperFunctions.h"

class Game
{
public:
	Game();
	virtual ~Game() = default;
	bool Init();
	void Run();
	void signalHandler(int row, int col, tgui::EditBox::Ptr widget);
private:
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	std::shared_ptr<tgui::Gui> mGui;
	std::shared_ptr<Sudoku> mSudoku;
	sf::RenderWindow mWindow;
	tgui::EditBox::Ptr mSudokuEditBoxGrid[81];
	int mSudokuGrid[9][9];
};