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
	return true;
}

void Game::Run()
{
}
