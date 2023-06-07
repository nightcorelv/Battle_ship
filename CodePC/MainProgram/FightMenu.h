#pragma once
#include"UiButton.h"
#include "SaveLoad.h"
#include"Background.h"

class FightMenu
{
private:
	Background background;

	sf::Font font;

	//enemy number toggle texts
	sf::Text enemyNumberTogglesText[4];
	//enemy number toggles
	UiButton enemyNumberToggles[4]
	{
		UiButton("../Images/UI/Toggle/off/000.png","../Images/UI/Toggle/on/000.png",450, 100),
		UiButton("../Images/UI/Toggle/off/000.png","../Images/UI/Toggle/on/000.png",450, 150),
		UiButton("../Images/UI/Toggle/off/000.png","../Images/UI/Toggle/on/000.png",450, 200),
		UiButton("../Images/UI/Toggle/off/000.png","../Images/UI/Toggle/on/000.png",450, 250)
	};

	//enemy difficulty toggles texts
	sf::Text enemyDifficultyTogglesText[4];
	//enemy difficulty toggles
	UiButton enemyDifficultyToggles[4]
	{
		UiButton("../Images/UI/Toggle/off/000.png","../Images/UI/Toggle/on/000.png",450, 350),
		UiButton("../Images/UI/Toggle/off/000.png","../Images/UI/Toggle/on/000.png",450, 400),
		UiButton("../Images/UI/Toggle/off/000.png","../Images/UI/Toggle/on/000.png",450, 450),
		UiButton("../Images/UI/Toggle/off/000.png","../Images/UI/Toggle/on/000.png",450, 500)
	};

	//fight button text
	sf::Text fightText;
	//fight button
	UiButton fight = UiButton("../Images/UI/Button/off/000.png", "../Images/UI/Button/on/000.png", 585, 560);

	int clickColddown;

	//fight
	bool go;
public:

	void draw(sf::RenderWindow& window);

	void update(sf::RenderWindow& window);

	bool getGo() const;

	FightMenu();
	virtual ~FightMenu();
};

