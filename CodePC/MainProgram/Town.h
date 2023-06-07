#pragma once
#include "GameState.h"
#include "Background.h"
#include "UiButton.h"
#include "Market.h"
#include "SaveLoad.h"
#include "FightMenu.h"

class Town : public GameState
{
private:

	TownMenu currentMenu;

	sf::Text texts[7];
	sf::Font font;

	//ui
	Background background;
	Background bar;

	//buttons
	UiButton buttons[4]
	{
		UiButton("../Images/UI/FightButton/off/000.png","../Images/UI/FightButton/on/000.png",window.getSize().x - 150, window.getSize().y - 150),
		UiButton("../Images/UI/MarketButton/off/000.png","../Images/UI/MarketButton/on/000.png",0, 200),
		UiButton("../Images/UI/RepairButton/off/000.png","../Images/UI/RepairButton/on/000.png",0, 50),
		UiButton("../Images/UI/Button/off/000.png","../Images/UI/Button/on/000.png",window.getSize().x - 150, 60)
	};

	//fight menu
	FightMenu fightMenu;
	//market menu
	Market market;

	ShipType playerShipType;
	int playerGold;
	float playerCurrentLife;

	int textShowTime;
	int savedTextShowTime;

	bool requireShipWarning;
	bool fullLife;
	bool repairWarning;
	bool savedText;

public:
	Town();
	virtual ~Town();

	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;

};

