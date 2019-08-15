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

void Game::signalHandler(int row, int col, tgui::EditBox::Ptr editBox, tgui::Label::Ptr label)
{
	try
	{
		int enteredNum = std::stoi(editBox->getText().toAnsiString());
		

		if (!IsSafe(mSudokuGrid, row, col, enteredNum)) // If the given number is not safe then,
		{
			label->setText("Warning!");
			mSudokuGrid[row][col] = enteredNum;
		}
		else
		{
			std::cout << "Safe\n";
			mSudokuGrid[row][col] = enteredNum;
		}
	}
	catch (std::invalid_argument)
	{
		if (editBox->getText().toAnsiString().size() == 0)  // Remove the assigned number when the number is deleted
		{	
			mSudokuGrid[row][col] = 0;
			label->setText(""); // Remove the text
		}
		return;
	}
	
}

bool Game::Init()
{
	mWindow.create(sf::VideoMode(WIDTH, HEIGHT), "Sudoku!");
	mGui = std::make_shared<tgui::Gui>(mWindow); // Create the gui and attach it to the window

	
	return true;
}

void Game::Run()
{
	tgui::Label::Ptr winLabel = tgui::Label::create();
	winLabel->setPosition(720, 150);
	winLabel->setSize(267.2f, 78.7863f);
	winLabel->setTextSize(50);
	winLabel->getRenderer()->setTextColor(tgui::Color::Red);
	mGui->add(winLabel);

	tgui::Button::Ptr newGameButton = tgui::Button::create();
	newGameButton->setPosition(720, 520);
	newGameButton->setSize(190.f, 69.6667f);
	newGameButton->setTextSize(25);
	newGameButton->setText("New Game");
	mGui->add(newGameButton);

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
			mGui->add(editBox);
			editBox->connect("TextChanged", &Game::signalHandler, this, i, j, editBox, winLabel);
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

		sf::Vertex line1[2];
		line1[0].position = sf::Vector2f(150, 235);
		line1[0].color = sf::Color::Red;
		line1[1].position = sf::Vector2f(680, 235);
		line1[1].color = sf::Color::Red;

		sf::Vertex line2[2];
		line2[0].position = sf::Vector2f(150, 415);
		line2[0].color = sf::Color::Red;
		line2[1].position = sf::Vector2f(680, 415);
		line2[1].color = sf::Color::Red;

		sf::Vertex line3[2];
		line3[0].position = sf::Vector2f(325, 60);
		line3[0].color = sf::Color::Red;
		line3[1].position = sf::Vector2f(325, 590);
		line3[1].color = sf::Color::Red;

		sf::Vertex line4[2];
		line4[0].position = sf::Vector2f(505, 60);
		line4[0].color = sf::Color::Red;
		line4[1].position = sf::Vector2f(505, 590);
		line4[1].color = sf::Color::Red;

		mWindow.clear(sf::Color::White);

		mGui->draw(); // Draw all widgets
		mWindow.draw(line1, 2, sf::Lines);
		mWindow.draw(line2, 2, sf::Lines);
		mWindow.draw(line3, 2, sf::Lines);
		mWindow.draw(line4, 2, sf::Lines);
		mWindow.display();
	}
}
