#include "Game.h"

Game::Game()
{
}

bool Game::Init()
{
	mWindow.create(sf::VideoMode(WIDTH, HEIGHT), "Monty Hall Problem Simulator");
	mGui = std::make_shared<tgui::Gui>(mWindow); // Create the gui and attach it to the window

	// Initialising seed for random number generation
	srand(static_cast<unsigned int>(time(nullptr)));

	tgui::EditBox::Ptr sudokuArray[81];
	tgui::EditBox::Ptr editBox;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			editBox = tgui::EditBox::create();
			editBox->setPosition(150 + 60 * i, 60 + 60 * j);
			editBox->setSize(50, 50);
			sudokuArray[i * 9 + j] = editBox;
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			mGui->add(sudokuArray[i * 9 + j]);
		}
	}

	return true;
}

void Game::Run()
{

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

		mWindow.clear();
		mGui->draw(); // Draw all widgets
		mWindow.display();
	}
}
