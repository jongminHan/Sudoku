#include "Game.h"
#include <memory>

Game::Game()
{
	// Initialising seed for random number generation
	srand(static_cast<unsigned int>(time(nullptr)));

	// Creating an instance of Sudoku
	mSudoku = std::make_shared<Sudoku>();

	// Creating a seed for puzzle generation
	mSudoku->CreateSeed();

	// Generating the puzzle
	mSudoku->GenPuzzle();

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mSudokuGrid[i][j] = mSudoku->GetGrid(i, j);
		}
	}
}

void Game::signalHandler(int row, int col, tgui::EditBox::Ptr widget)
{
	mSudokuGrid[row][col] = std::stoi(widget->getText().toAnsiString());
}

bool Game::Init()
{
	mWindow.create(sf::VideoMode(WIDTH, HEIGHT), "Sudoku!");
	mGui = std::make_shared<tgui::Gui>(mWindow); // Create the gui and attach it to the window

	return true;
}

void Game::Run()
{
	tgui::EditBox::Ptr editBox;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			editBox = tgui::EditBox::create();
			editBox->setPosition(150 + 60 * i, 60 + 60 * j);
			editBox->setSize(50, 50);
			editBox->setAlignment(tgui::EditBox::Alignment::Center);

			int gridNum = mSudokuGrid[i][j];

			if (gridNum != 0) // Show no number if the given number is zero.
			{
				sf::String sfStr(std::to_string(gridNum));
				editBox->setDefaultText(sfStr);
				editBox->setEnabled(false);
			}

			mSudokuEditBoxGrid[i * 9 + j] = editBox;

			editBox->connect("TextChanged", &Game::signalHandler, this, i, j, editBox);
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mGui->add(mSudokuEditBoxGrid[i * 9 + j]);
		}
	}

	while (mWindow.isOpen())
	{
		sf::Event event;
		while (mWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				mWindow.close();
			}

			mGui->handleEvent(event); // Pass the event to the widgets
		}

		mWindow.clear(sf::Color::White);
		mGui->draw(); // Draw all widgets
		mWindow.display();
	}
}
