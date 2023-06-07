#pragma once
#include "Ship.h"
#include "Explotion.h"
#include"Background.h"
#include"SaveLoad.h"

class ShipHandler
{
private:
	sf::Font font;
	Background background;

	//player
	Ship* playerShip;
	sf::Text playerLifeText;

	//enemy
	Ship** enemyShips;
	sf::Text** enemyLifeText;

	int nrOfEnemy;
	bool win;
	bool lose;

	int playerGold;
	float playerCurrentLife;

	std::string difficulty;
	int rewards;

	sf::RenderWindow& window;

public:

	void update();
	void draw();
	bool getWin() const;
	bool getLose() const;

	ShipHandler(sf::RenderWindow& window);
	~ShipHandler();
};

