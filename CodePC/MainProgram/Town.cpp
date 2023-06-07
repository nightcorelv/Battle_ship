#include "Town.h"
#include "State.h"

Town::Town()
	:GameState("Game"),
	background("../Images/Backgrounds/Town/000.png", 0, 0),
	market(0, ShipType::None),
	currentMenu(TownMenu::None),
	bar("../Images/UI/Bar/000.png", 0, 0),
	textShowTime(0),
	savedTextShowTime(0),
	requireShipWarning(false),
	fullLife(false),
	repairWarning(false),
	savedText(false)
{
	window.setFramerateLimit(70);

	//load save
	SaveLoad::load(playerShipType, playerGold, playerCurrentLife);


#pragma region TextInit

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	//save button
	texts[0].setFont(font);
	texts[0].setFillColor(sf::Color::Blue);
	texts[0].setCharacterSize(30);
	texts[0].setString("Save");
	texts[0].setPosition(window.getSize().x - 125, 65);

	//require warning
	texts[1].setFont(font);
	texts[1].setFillColor(sf::Color::Red);
	texts[1].setCharacterSize(60);
	texts[1].setOutlineThickness(5);
	texts[1].setString("Require a Ship");
	texts[1].setPosition(window.getSize().x * 0.5 - 170, window.getSize().y * 0.5 - 300);

	//gold
	texts[2].setFont(font);
	texts[2].setFillColor(sf::Color::Red);
	texts[2].setCharacterSize(20);
	texts[2].setOutlineThickness(3);
	texts[2].setPosition(window.getSize().x * 0.5 - 50, 0);
	texts[2].setString("Golds : " + std::to_string(playerGold));

	//hp
	texts[3].setFont(font);
	texts[3].setFillColor(sf::Color::Red);
	texts[3].setCharacterSize(20);
	texts[3].setOutlineThickness(3);
	texts[3].setPosition(window.getSize().x * 0.5 - 300, 0);

	//ship type
	texts[4].setFont(font);
	texts[4].setFillColor(sf::Color::Red);
	texts[4].setCharacterSize(20);
	texts[4].setOutlineThickness(3);
	texts[4].setPosition(window.getSize().x * 0.5 + 300, 0);
	if (playerShipType == ShipType::None)
	{
		texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 0");
		texts[4].setString("Ship : None");
	}
	else if (playerShipType == ShipType::Normal_Ship)
	{
		texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 100");
		texts[4].setString("Ship : Normal Ship");
	}
	else if (playerShipType == ShipType::Speed_Ship)
	{
		texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 120");
		texts[4].setString("Ship : Speed Ship");
	}
	else if (playerShipType == ShipType::Creators_Ship)
	{
		texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 150");
		texts[4].setString("Ship : Creators Ship");
	}

	//repair ship warning
	texts[5].setFont(font);
	texts[5].setFillColor(sf::Color::Red);
	texts[5].setCharacterSize(60);
	texts[5].setOutlineThickness(5);
	texts[5].setPosition(window.getSize().x * 0.5 - 350, window.getSize().y * 0.5 - 300);
	texts[5].setString("Ship needs to be repaired");

	//saved warning
	texts[6].setFont(font);
	texts[6].setFillColor(sf::Color::Green);
	texts[6].setCharacterSize(60);
	texts[6].setOutlineThickness(5);
	texts[6].setPosition(window.getSize().x * 0.5 - 50, window.getSize().y * 0.5 - 100);
	texts[6].setString("Saved");

#pragma endregion

}

Town::~Town()
{

}

State Town::update()
{
	State state = State::NO_CHANGE;

	//town menu action
	if (currentMenu == TownMenu::None)
	{
		//update show warnings
		if (requireShipWarning || repairWarning)
		{
			textShowTime++;
		}
		if (textShowTime > 90)
		{
			requireShipWarning = false;
			repairWarning = false;
			textShowTime = 0;
		}
		if (savedText)
		{
			savedTextShowTime++;
		}
		if (savedTextShowTime > 90)
		{
			savedText = false;
			savedTextShowTime = 0;
		}

		//update buttons
		for (int i = 0; i < 4; i++)
		{
			buttons[i].update();
		}

		//buttons events
		//fight
		if (buttons[0].getFinnishDelay())
		{
			if (playerShipType == ShipType::None)
			{
				requireShipWarning = true;
				textShowTime = 0;
			}
			else if (playerShipType != ShipType::None && !fullLife)
			{
				repairWarning = true;
				textShowTime = 0;
			}
			else if(playerShipType != ShipType::None && fullLife)
			{
				currentMenu = TownMenu::Fight;//state = State::FIGHT;
			}
			buttons[0].reset();
		}
		//market
		else if (buttons[1].getFinnishDelay())
		{
			market.updatePlayerInfo(playerShipType, playerGold);
			currentMenu = TownMenu::Market;
			buttons[1].reset();
		}
		//repair
		else if (buttons[2].getFinnishDelay())
		{
			if (playerShipType == ShipType::None)
			{
				requireShipWarning = true;
				textShowTime = 0;
			}
			else if (playerShipType == ShipType::Normal_Ship)
			{
				playerCurrentLife = 100;
				fullLife = true;
				texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 100");
			}
			else if (playerShipType == ShipType::Speed_Ship)
			{
				playerCurrentLife = 120;
				fullLife = true;
				texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 120");
			}
			else if (playerShipType == ShipType::Creators_Ship)
			{
				playerCurrentLife = 150;
				fullLife = true;
				texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 150");
			}

			buttons[2].reset();
		}
		//save
		else if (buttons[3].getFinnishDelay())
		{
			SaveLoad::save(playerShipType, playerGold, playerCurrentLife);
			savedText = true;
			savedTextShowTime = 0;
			buttons[3].reset();
		}

	}
	//Market Menu action
	else if (currentMenu == TownMenu::Market)
	{
		market.update();
	}
	//fight Menu action
	else if (currentMenu == TownMenu::Fight)
	{
		//check if go
		if (fightMenu.getGo())
		{
			state = State::FIGHT;
		}
		else//update
		{
			fightMenu.update(window);
		}
	}

	return state;
}

void Town::render()
{
	window.clear();

	//Town Ui
	if (currentMenu == TownMenu::None)
	{
		// background and bar
		window.draw(background);
		window.draw(bar);

		//buttons
		window.draw(buttons[0]);
		window.draw(buttons[1]);
		window.draw(buttons[2]);
		window.draw(buttons[3]);

		//warnings
		if (playerShipType == ShipType::None && requireShipWarning)
		{
			window.draw(texts[1]);
		}
		else if (playerShipType != ShipType::None && repairWarning)
		{
			window.draw(texts[5]);
		}

		//texts
		window.draw(texts[0]);
		window.draw(texts[2]);
		window.draw(texts[3]);
		window.draw(texts[4]);

		//saved text
		if (savedText)
		{
			window.draw(texts[6]);
		}

	}
	//market Ui
	else if (currentMenu == TownMenu::Market)
	{
		market.draw(window);
	}
	else if (currentMenu == TownMenu::Fight)
	{
		fightMenu.draw(window);
	}

	window.display();
}

void Town::handleEvents()
{
	//check if back from market
	if (market.backToTown())
	{
		currentMenu = TownMenu::None;
		market.reset();
		SaveLoad::load(playerShipType, playerGold, playerCurrentLife);

		texts[2].setString("Golds : " + std::to_string(playerGold));
		if (playerShipType == ShipType::None)
		{
			texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 0");
			texts[4].setString("Ship : None");
			fullLife = false;
		}
		else if (playerShipType == ShipType::Normal_Ship)
		{
			texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 100");
			texts[4].setString("Ship : Normal Ship");

			if (playerCurrentLife >= 100)
			{
				fullLife = true;
			}
			else
			{
				fullLife = false;
			}
		}
		else if (playerShipType == ShipType::Speed_Ship)
		{
			texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 120");
			texts[4].setString("Ship : Speed Ship");

			if (playerCurrentLife >= 120)
			{
				fullLife = true;
			}
			else
			{
				fullLife = false;
			}
		}
		else if (playerShipType == ShipType::Creators_Ship)
		{
			texts[3].setString("HP : " + std::to_string((int)playerCurrentLife) + " / 150");
			texts[4].setString("Ship : Creators Ship");

			if (playerCurrentLife >= 150)
			{
				fullLife = true;
			}
			else
			{
				fullLife = false;
			}
		}
	}

	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		//mouse events for town
		if (currentMenu == TownMenu::None)
		{
			//if mouse is hold in button
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < 4; i++)
					{
						if (buttons[i].mouseOver(window))
						{
							buttons[i].setIsOn(true);
						}
						else
						{
							buttons[i].setIsOn(false);
						}
					}
				}
			}

			//if mouse released
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					for (int i = 0; i < 4; i++)
					{
						if (buttons[i].mouseOver(window))
						{
							buttons[i].setClicked(true);
						}
						buttons[i].setIsOn(false);

					}
				}
			}
		}
		//market
		else if (currentMenu == TownMenu::Market)
		{
			market.handleEvent(event, window);
		}

	}
}


