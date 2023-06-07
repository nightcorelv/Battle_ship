#include "ShipHandler.h"

ShipHandler::ShipHandler(sf::RenderWindow& window)
	:nrOfEnemy(-1),
	playerShip(nullptr),
	enemyShips(nullptr),
	window(window),
	win(false),
	background("../Images/Backgrounds/Fight/000.png", 0, 0),
	enemyLifeText(nullptr),
	lose(false)
{
	SaveLoad::loadFightInfo(difficulty, nrOfEnemy, rewards);

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");
	ShipType type;
	//load file
	SaveLoad::load(type, playerGold, playerCurrentLife);
	//player
	playerShip = new Ship(type, nullptr, true);
	//background
	background.setScale(0.6, 0.6);
	//enemy
	if (nrOfEnemy > 0)
	{
		//enemy obj
		enemyShips = new Ship * [nrOfEnemy];
		enemyLifeText = new sf::Text * [nrOfEnemy];
		for (int i = 0; i < nrOfEnemy; i++)
		{

			ShipType enemyShipType = ShipType::None;
			//Easy
			if (difficulty == "Easy")
			{
				enemyShipType = ShipType::Normal_Ship;
			}
			//Normal
			else if (difficulty == "Normal")
			{
				enemyShipType = ShipType::Speed_Ship;
			}
			//hard
			else if (difficulty == "Hard")
			{
				enemyShipType = ShipType::Creators_Ship;
			}
			//random ship type
			else if (difficulty == "Random")
			{
				int seed = rand() % 3;
				if (seed == 0)
				{
					enemyShipType = ShipType::Normal_Ship;
				}
				else if (seed == 1)
				{
					enemyShipType = ShipType::Speed_Ship;
				}
				else if (seed == 2)
				{
					enemyShipType = ShipType::Creators_Ship;
				}
			}
			//enemy init
			enemyShips[i] = new Ship(enemyShipType, playerShip, false);

			//enemy life text 
			enemyLifeText[i] = new sf::Text();
			enemyLifeText[i]->setFont(font);
			enemyLifeText[i]->setFillColor(sf::Color::Red);
			enemyLifeText[i]->setCharacterSize(15);
			enemyLifeText[i]->setOutlineThickness(2);
			enemyLifeText[i]->setPosition(0, 0);
			enemyLifeText[i]->setString("HP: " + std::to_string((int)enemyShips[i]->getCurrentLife()));

		}
		//get player targets
		playerShip->setTargets(enemyShips, nrOfEnemy);
	}
	//player life text
	playerLifeText.setFont(font);
	playerLifeText.setFillColor(sf::Color::Green);
	playerLifeText.setCharacterSize(15);
	playerLifeText.setOutlineThickness(2);
	playerLifeText.setPosition(0, 0);
	playerLifeText.setString("HP: " + std::to_string((int)playerShip->getCurrentLife()));
}

ShipHandler::~ShipHandler()
{
	delete playerShip;

	if (nrOfEnemy > 0)
	{
		for (int i = 0; i < nrOfEnemy; i++)
		{
			if (enemyShips[i] != nullptr)
			{
				delete enemyShips[i];
				delete enemyLifeText[i];
			}
		}
	}
	if (enemyShips != nullptr)
	{
		delete[] enemyShips;
	}
	if (enemyLifeText != nullptr)
	{
		delete[] enemyLifeText;
	}
}

void ShipHandler::update()
{
	//player move
	playerShip->move(window);
	playerLifeText.setPosition(playerShip->getPosition().x, playerShip->getPosition().y - 30);
	playerLifeText.setString("HP: " + std::to_string((int)playerShip->getCurrentLife()));

	for (int i = 0; i < 3; i++)
	{
		playerShip->getBulletLeft(i)->getExplotion()->play();
		playerShip->getBulletRight(i)->getExplotion()->play();
	}

	//enemy move
	int enemyLeft = 0;
	if (nrOfEnemy > 0)
	{
		for (int i = 0; i < nrOfEnemy; i++)
		{
			if (enemyShips[i]->getCurrentLife() > 0)
			{
				enemyLeft++;
			}
			enemyShips[i]->move(window);

			if (!enemyShips[i]->getDead())
			{
				enemyLifeText[i]->setPosition(enemyShips[i]->getPosition().x, enemyShips[i]->getPosition().y - 30);
				enemyLifeText[i]->setString("HP: " + std::to_string((int)enemyShips[i]->getCurrentLife()));
			}

			for (int k = 0; k < 3; k++)
			{
				enemyShips[i]->getBulletLeft(k)->getExplotion()->play();
				enemyShips[i]->getBulletRight(k)->getExplotion()->play();
			}
		}
	}
	if (enemyLeft <= 0)
	{
		//win, save to file
		SaveLoad::save(playerShip->getShipType(), playerGold + rewards, playerShip->getCurrentLife());
		win = true;
	}
	else if (playerShip->getCurrentLife() <= 0)
	{
		//lose, save to file
		SaveLoad::save(playerShip->getShipType(), playerGold, 0);
		lose = true;
	}
}

void ShipHandler::draw()
{
	window.draw(background);
	//player
	playerShip->drawOut(window);

	//enemy
	if (nrOfEnemy > 0)
	{
		for (int i = 0; i < nrOfEnemy; i++)
		{
			enemyShips[i]->drawOut(window);
		}

		//draw explotion
		for (int i = 0; i < nrOfEnemy; i++)
		{

			for (int k = 0; k < 3; k++)
			{
				if (!enemyShips[i]->getBulletLeft(k)->getExplotion()->getFinnish())
				{
					window.draw(*enemyShips[i]->getBulletLeft(k)->getExplotion());
				}
				if (!enemyShips[i]->getBulletRight(k)->getExplotion()->getFinnish())
				{
					window.draw(*enemyShips[i]->getBulletRight(k)->getExplotion());
				}
			}
			//life text
			if (!enemyShips[i]->getDead())
			{
				window.draw(*enemyLifeText[i]);
			}
		}
	}

	//draw player explotion
	for (int i = 0; i < 3; i++)
	{
		if (!playerShip->getBulletLeft(i)->getExplotion()->getFinnish())
		{
			window.draw(*playerShip->getBulletLeft(i)->getExplotion());
		}
		if (!playerShip->getBulletRight(i)->getExplotion()->getFinnish())
		{
			window.draw(*playerShip->getBulletRight(i)->getExplotion());
		}
	}

	window.draw(playerLifeText);
}

bool ShipHandler::getWin() const
{
	return win;
}

bool ShipHandler::getLose() const
{
	return lose;
}
