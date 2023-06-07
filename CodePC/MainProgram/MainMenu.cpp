#include "MainMenu.h"
#include <iostream>


MainMenu::MainMenu()
	:GameState("Menu"),background("../Images/Backgrounds/Main/000.png", 0, 0)
{
	window.setFramerateLimit(70);
	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	alternatives[0].setFont(font);
	alternatives[0].setFillColor(sf::Color::Blue);
	alternatives[0].setCharacterSize(30);
	alternatives[0].setString("Play");
	alternatives[0].setPosition(1125.f, 300.f);

	alternatives[1].setFont(font);
	alternatives[1].setFillColor(sf::Color::Blue);
	alternatives[1].setCharacterSize(30);
	alternatives[1].setString("Load");
	alternatives[1].setPosition(1120.f, 450.f);

	alternatives[2].setFont(font);
	alternatives[2].setFillColor(sf::Color::Blue);
	alternatives[2].setCharacterSize(30);
	alternatives[2].setString("Exit");
	alternatives[2].setPosition(1125.f, 600.f);
}

MainMenu::~MainMenu()
{

}

State MainMenu::update()
{
	State state = State::NO_CHANGE;

	for (int i = 0; i < 3; i++)
	{
		if (buttons[i].mouseOver(window))
		{
			alternatives[i].setFillColor(sf::Color::Red);
		}
		else
		{
			alternatives[i].setFillColor(sf::Color::Blue);
		}
	}

	if (buttons[0].getIsOn())
	{
		SaveLoad::save(ShipType::None, 20000, 0);
		state = State::TOWN;
	}
	else if (buttons[1].getIsOn())
	{

		state = State::TOWN;
	}
	else if (buttons[2].getIsOn())
	{
		state = State::EXIT;
	}

	return state;
}

void MainMenu::render()
{
	window.clear();

	window.draw(background);
	window.draw(buttons[0]);
	window.draw(buttons[1]);
	window.draw(buttons[2]);
	window.draw(alternatives[0]);
	window.draw(alternatives[1]);
	window.draw(alternatives[2]);

	window.display();
}

void MainMenu::handleEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		//click event
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (buttons[0].mouseOver(window))
				{
					buttons[0].setIsOn(true);
				}
				else if (buttons[1].mouseOver(window))
				{
					buttons[1].setIsOn(true);
				}
				else if (buttons[2].mouseOver(window))
				{
					buttons[2].setIsOn(true);
				}
			}
		}

	}
}

