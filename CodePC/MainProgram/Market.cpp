#include "Market.h"

void Market::updatePlayerInfo(ShipType shipType, int gold)
{
	playerShipType = shipType;
	playerGold = gold;
}

void Market::handleEvent(sf::Event& event, sf::RenderWindow& window)
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

void Market::update()
{
	//update buttons
	for (int i = 0; i < 4; i++)
	{
		buttons[i].update();
	}

	//buy
	if (buttons[0].getFinnishDelay())
	{
		if (selectedShip == ShipType::Normal_Ship && playerGold >= 20000 && playerShipType != ShipType::Normal_Ship)
		{
			playerGold -= 20000;
			playerShipType = ShipType::Normal_Ship;
			SaveLoad::save(playerShipType, playerGold, 0);
		}
		else if (selectedShip == ShipType::Speed_Ship && playerGold >= 30000 && playerShipType != ShipType::Speed_Ship)
		{
			playerGold -= 30000;
			playerShipType = ShipType::Speed_Ship;
			SaveLoad::save(playerShipType, playerGold, 0);
		}
		else if (selectedShip == ShipType::Creators_Ship && playerGold >= 70000 && playerShipType != ShipType::Creators_Ship)
		{
			playerGold -= 70000;
			playerShipType = ShipType::Creators_Ship;
			SaveLoad::save(playerShipType, playerGold, 0);
		}
		buttons[0].reset();
	}
	//back
	if (buttons[1].getFinnishDelay())
	{
		back = true;
		buttons[1].reset();
	}
	//next ship
	if (buttons[2].getFinnishDelay())
	{
		if (selectedShip == ShipType::Normal_Ship)
		{
			selectedShip = ShipType::Speed_Ship;
			showLast = true;
			showNext = true;
			buttonTexts[2].setString("30000");
		}
		else if (selectedShip == ShipType::Speed_Ship)
		{
			selectedShip = ShipType::Creators_Ship;
			showNext = false;
			buttonTexts[2].setString("70000");
		}
		else if (selectedShip == ShipType::Creators_Ship)
		{
			
		}
		buttons[2].reset();
	}
	//last ship
	if (buttons[3].getFinnishDelay())
	{
		if (selectedShip == ShipType::Normal_Ship)
		{

		}
		else if (selectedShip == ShipType::Speed_Ship)
		{
			selectedShip = ShipType::Normal_Ship;
			showLast = false;
			showNext = true;
			buttonTexts[2].setString("20000");
		}
		else if (selectedShip == ShipType::Creators_Ship)
		{
			selectedShip = ShipType::Speed_Ship;
			showLast = true;
			showNext = true;
			buttonTexts[2].setString("30000");
		}
		buttons[3].reset();
	}
}

void Market::draw(sf::RenderWindow& window)
{
    window.draw(background);

	//show ship by type
	if (selectedShip == ShipType::Normal_Ship)
	{
		window.draw(icons[0]);
	}
	else if (selectedShip == ShipType::Speed_Ship)
	{
		window.draw(icons[1]);
	}
	else if (selectedShip == ShipType::Creators_Ship)
	{
		window.draw(icons[2]);
	}

    window.draw(buttons[0]);//buy
    window.draw(buttons[1]);//back
	if (showNext)
	{
		window.draw(buttons[2]);//next
	}
	if (showLast)
	{
		window.draw(buttons[3]);//last
	}
	
    window.draw(buttonTexts[0]);//buy
    window.draw(buttonTexts[1]);//back
	window.draw(buttonTexts[2]);//cost
}

bool Market::backToTown() const
{
	return back;
}

void Market::reset()
{
	back = false;
	selectedShip = ShipType::Normal_Ship;
	showNext = true;
	showLast = false;
}



Market::Market(int playerGold, ShipType playerShipType)
	:background(Background("../Images/UI/Market/000.png", 407, 30)) ,
    playerGold(playerGold),
    playerShipType(playerShipType),
    selectedShip(ShipType::Normal_Ship),
	back(false),
	showNext(true),
	showLast(false)
{

    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    buttonTexts[0].setFont(font);
    buttonTexts[0].setFillColor(sf::Color::Blue);
    buttonTexts[0].setCharacterSize(30);
    buttonTexts[0].setString("Buy");
    buttonTexts[0].setPosition(617, 565);

    buttonTexts[1].setFont(font);
    buttonTexts[1].setFillColor(sf::Color::Blue);
    buttonTexts[1].setCharacterSize(30);
    buttonTexts[1].setString("Back");
    buttonTexts[1].setPosition(25, 5);

	buttonTexts[2].setFont(font);
	buttonTexts[2].setFillColor(sf::Color::Red);
	buttonTexts[2].setCharacterSize(30);
	buttonTexts[2].setPosition(600, 500);
	buttonTexts[2].setOutlineThickness(2);
	buttonTexts[2].setString("20000");
}


Market::~Market()
{

}
