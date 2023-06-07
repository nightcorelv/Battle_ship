#include "Game.h"
#include <iostream>
#include "State.h"

Game::Game()
	:GameState("Game"),
	paused(true),
	control("../Images/UI/Control/000.png", 0, 0),
	pausedColddown(60),
	handler(ShipHandler(window))
{

	window.setFramerateLimit(70);
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);

	pauseButton.setIsOn(true);
}

Game::~Game()
{

}

State Game::update()
{
	State state = State::NO_CHANGE;

	elapsedTimeSinceLastUpdate += clock.restart();

	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;

		//pause Colddown
		if (pausedColddown <= 60)
		{
			pausedColddown++;
		}

		//if win or lose
		if (handler.getWin() || handler.getLose())
		{
			state = State::TOWN;
		}

		if (paused)
		{
			//unpause
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) || pauseButton.mouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && pausedColddown >= 60)
			{
				paused = false;
				pauseButton.setIsOn(false);
				pausedColddown = 0;
			}

		}
		else
		{
			//pressed pause
			if (pauseButton.mouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && pausedColddown >= 60)
			{
				paused = true;
				pauseButton.setIsOn(true);
				pausedColddown = 0;
			}
			//update
			handler.update();
		}

	}

	return state;
}

void Game::render()
{

	window.clear();

	handler.draw();
	if (paused)
	{
		window.draw(control);
	}
	window.draw(pauseButton);

	window.display();
}

void Game::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

	}
}






