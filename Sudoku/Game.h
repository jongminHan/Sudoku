#pragma once
#include <TGUI/TGUI.hpp>
#include <memory>
#include "Sudoku.h"
#include "HelperFunctions.h"

class Game
{
public:
	Game();
	virtual ~Game() = default;
	bool Init();
	void Run();
	void CreateNewGameSignal();
	void CreateNewGameSignalFromChild(tgui::ChildWindow::Ptr childWindow);
	void signalHandler(int row, int col, tgui::EditBox::Ptr widget, tgui::Label::Ptr label);
private:
	const int WIDTH = 1280;
	const int HEIGHT = 720;
	std::shared_ptr<tgui::Gui> mGui;
	std::shared_ptr<Sudoku> mSudoku; // 스도쿠 게임
	sf::RenderWindow mWindow;
	tgui::EditBox::Ptr mSudokuEditBoxGrid[81]; // 스도쿠 숫자 입력 상자들
	int mSudokuGrid[9][9]; // 스도쿠 격자 상태 저장
};