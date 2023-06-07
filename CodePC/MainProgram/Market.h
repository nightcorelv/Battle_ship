#pragma once
#include "Ship.h"
#include "UiButton.h"
#include"Background.h"
#include"SaveLoad.h"

class Market
{
private:

	Background background;
	ShipType playerShipType;
	int playerGold;

	ShipType selectedShip;

	//ship icons
	Background icons[3]
	{
		Background("../Images/UI/IconNB/000.png", 520, 100),
		Background("../Images/UI/IconSB/000.png", 490, 100),
		Background("../Images/UI/IconCB/000.png", 430, 100)
	};

	sf::Text buttonTexts[3];
	sf::Font font;

	//buttons
	UiButton buttons[4]
	{
		UiButton("../Images/UI/Button/off/000.png","../Images/UI/Button/on/000.png", 585, 560),
		UiButton("../Images/UI/Button/off/000.png","../Images/UI/Button/on/000.png", 0, 0),
		UiButton("../Images/UI/MarketNextBoat/000.png","../Images/UI/MarketNextBoat/000.png",1000, 300),
		UiButton("../Images/UI/MarketLastBoat/000.png","../Images/UI/MarketLastBoat/000.png",180, 300)
	};

	bool back;
	bool showNext;
	bool showLast;

public:

	void updatePlayerInfo(ShipType shipType, int gold);
	void handleEvent(sf::Event& event,sf::RenderWindow& window);
	void update();
	void draw(sf::RenderWindow& window);
	bool backToTown() const;
	void reset();

	Market(int playerGold, ShipType playerShipType);
	virtual ~Market();
};

