#include "Ship.h"

void Ship::spawn(int x, int y)
{
	setPosition(x, y);
}

void Ship::fireLeft()
{
	//check if available to shoot
	if (availableToFireLeft)
	{
		timeCountLeft = 0;
		hasShootLeft = true;
		availableToFireLeft = false;

		bulletLeft[0].shoot(getShipPosition(), getShipRotation() - 90);

		int bulletDistance = 13;

		sf::Vector2f shipPosition = sf::Vector2f(getShipPosition().x + (cos(getShipRotation() * 3.14 / 180.0) * bulletDistance), getShipPosition().y + (sin(getShipRotation() * 3.14 / 180.0) * bulletDistance));
		bulletLeft[1].shoot(shipPosition, getShipRotation() - 90);

		shipPosition = sf::Vector2f(getShipPosition().x + (cos(getShipRotation() * 3.14 / 180.0) * -bulletDistance), getShipPosition().y + (sin(getShipRotation() * 3.14 / 180.0) * -bulletDistance));
		bulletLeft[2].shoot(shipPosition, getShipRotation() - 90);
	}
}

void Ship::fireRight()
{
	//check if available to shoot
	if (availableToFireRight)
	{
		timeCountRight = 0;
		hasShootRight = true;
		availableToFireRight = false;

		bulletRight[0].shoot(getShipPosition(), getShipRotation() + 90);

		int bulletDistance = 13;

		sf::Vector2f shipPosition = sf::Vector2f(getShipPosition().x + (cos(getShipRotation() * 3.14 / 180.0) * bulletDistance), getShipPosition().y + (sin(getShipRotation() * 3.14 / 180.0) * bulletDistance));
		bulletRight[1].shoot(shipPosition, getShipRotation() + 90);

		shipPosition = sf::Vector2f(getShipPosition().x + (cos(getShipRotation() * 3.14 / 180.0) * -bulletDistance), getShipPosition().y + (sin(getShipRotation() * 3.14 / 180.0) * -bulletDistance));
		bulletRight[2].shoot(shipPosition, getShipRotation() + 90);
	}

}

void Ship::setTarget(Ship* targetShip)
{
	target = targetShip;
}

void Ship::setTargets(Ship** targetShips, int nrOf)
{
	targets = targetShips;
	nrOfTargets = nrOf;
}

Ship::Ship()
	: Ship(ShipType::Normal_Ship, nullptr, false)
{

}

Ship::Ship(ShipType type, Ship* target, bool isplayer)
	: ShipStats(type),
	isPlayer(isplayer),
	target(target),
	targets(nullptr),
	bulletLeft(new Bullet[3]),
	bulletRight(new Bullet[3]),
	availableToFireLeft(true),
	availableToFireRight(true),
	hasShootLeft(false),
	hasShootRight(false),
	timeCountLeft(0),
	timeCountRight(0),
	nrOfTargets(0)
{
	if (isPlayer)
	{
		setDrawLine(true);
		setShipPosition(1280/2, 720/2);
	}
	else
	{
		setShipPosition(rand() % 1280, rand() % 720);
	}

	loadShipTexture(type);
}

Ship::~Ship()
{
	delete[] bulletLeft;
	delete[] bulletRight;
}

void Ship::move(sf::RenderWindow& window)
{
	//colddown left, 180 = 3 sec
	if (timeCountLeft > 180)
	{
		availableToFireLeft = true;
		hasShootLeft = false;
	}
	else
	{
		timeCountLeft++;//add one per frame after shoot
	}

	//colddown right, 180 = 3 sec
	if (timeCountRight > 180)
	{
		availableToFireRight = true;
		hasShootRight = false;
	}
	else
	{
		timeCountRight++;//add one per frame after shoot
	}

	// has shoot left
	if (hasShootLeft)
	{
		for (int i = 0; i < 3; i++)
		{
			if (targets != nullptr && nrOfTargets > 0)
			{
				for (int k = 0; k < nrOfTargets; k++)
				{
					if (targets[k] != nullptr && !targets[k]->getDead() && bulletLeft[i].getBounds().intersects(targets[k]->getShipBounds()))
					{
						bulletLeft[i].hit(targets[k]);
					}
				}
			}
			if (!bulletLeft[i].getHitShip() && target != nullptr && !target->getDead() && bulletLeft[i].getBounds().intersects(target->getShipBounds()))
			{
				bulletLeft[i].hit(target);
			}
			if(!bulletLeft[i].getHitShip())
			{
				bulletLeft[i].move(window);
			}
		}
	}
	// has shoot right
	if (hasShootRight)
	{
		for (int i = 0; i < 3; i++)
		{
			if (targets != nullptr)
			{
				for (int k = 0; k < nrOfTargets; k++)
				{
					if (targets[k] != nullptr && bulletRight[i].getBounds().intersects(targets[k]->getShipBounds()))
					{
						bulletRight[i].hit(targets[k]);
					}
				}
			}
			if (!bulletRight[i].getHitShip() && target != nullptr && bulletRight[i].getBounds().intersects(target->getShipBounds()))
			{
				bulletRight[i].hit(target);
			}
			if (!bulletRight[i].getHitShip())
			{
				bulletRight[i].move(window);
			}
		}
	}

	//player movement
	if (isPlayer)
	{
		//move
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::Vector2f shipPosition = this->getPosition();

			float shipSin = sin(getShipRotation() * 3.14 / 180) * -1;
			float mouseSin = (mousePosition.y - shipPosition.y) / sqrt(((mousePosition.y - shipPosition.y) * (mousePosition.y - shipPosition.y)) + ((mousePosition.x - shipPosition.x) * (mousePosition.x - shipPosition.x))) * -1;

			if (getShipRotation() >= 270 || getShipRotation() <= 90)
			{
				if (mousePosition.x > shipPosition.x && mouseSin <= shipSin)
				{
					rotateTo(1 * getSpeed());

				}
				else if (mousePosition.x > shipPosition.x && mouseSin > shipSin)
				{
					rotateTo(-1 * getSpeed());
				}
				else if (mousePosition.x < shipPosition.x)
				{
					if (mouseSin >= shipSin * -1)
					{
						rotateTo(-1 * getSpeed());
					}
					else
					{
						rotateTo(1 * getSpeed());
					}

				}
			}
			else if (getShipRotation() < 270 && getShipRotation() > 90)
			{
				if (mousePosition.x < shipPosition.x && mouseSin >= shipSin)
				{
					rotateTo(1 * getSpeed());
				}
				else if (mousePosition.x < shipPosition.x && mouseSin < shipSin)
				{
					rotateTo(-1 * getSpeed());
				}
				else if (mousePosition.x > shipPosition.x)
				{
					if (mouseSin >= shipSin * -1)
					{
						rotateTo(1 * getSpeed());
					}
					else
					{
						rotateTo(-1 * getSpeed());
					}
				}
			}
		}
		//fire
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			sf::Vector2f shipPosition = this->getPosition();

			float shipSin = sin(getShipRotation() * 3.14 / 180) * -1;
			float mouseSin = (mousePosition.y - shipPosition.y) / sqrt(((mousePosition.y - shipPosition.y) * (mousePosition.y - shipPosition.y)) + ((mousePosition.x - shipPosition.x) * (mousePosition.x - shipPosition.x))) * -1;

			if (getShipRotation() >= 270 || getShipRotation() <= 90)
			{
				if (mousePosition.x > shipPosition.x && mouseSin <= shipSin)
				{
					fireRight();
				}
				else if (mousePosition.x > shipPosition.x && mouseSin > shipSin)
				{
					fireLeft();
				}
				else if (mousePosition.x < shipPosition.x)
				{
					if (mouseSin >= shipSin * -1)
					{
						fireLeft();
					}
					else
					{
						fireRight();
					}
				}
			}
			else if (getShipRotation() < 270 && getShipRotation() > 90)
			{
				if (mousePosition.x < shipPosition.x && mouseSin >= shipSin)
				{
					fireRight();
				}
				else if (mousePosition.x < shipPosition.x && mouseSin < shipSin)
				{
					fireLeft();
				}
				else if (mousePosition.x > shipPosition.x)
				{
					if (mouseSin >= shipSin * -1)
					{
						fireRight();
					}
					else
					{
						fireLeft();
					}
				}
			}
		}
	}
	//enemy movement
	else if (!isPlayer && target != nullptr)
	{
		sf::Vector2f targetSinPosition = target->getPosition();
		sf::Vector2f shipPosition = this->getPosition();
		float rotation = this->getShipRotation();

		float shipSin = sin(getShipRotation() * 3.14 / 180) * -1;
		float targetSin = (targetSinPosition.y - shipPosition.y) / sqrt(((targetSinPosition.y - shipPosition.y) * (targetSinPosition.y - shipPosition.y)) + ((targetSinPosition.x - shipPosition.x) * (targetSinPosition.x - shipPosition.x))) * -1;

		float distance = sqrt(((shipPosition.x - targetSinPosition.x) * (shipPosition.x - targetSinPosition.x)) + ((shipPosition.y - targetSinPosition.y) * (shipPosition.y - targetSinPosition.y)));
		double targetTan = tan(target->getShipRotation() * 3.14 / 180);
		double shipTan = tan(getShipRotation() * 3.14 / 180);
		bool onRightSide = false;

		if (rotation >= 270 || rotation <= 90)
		{
			if (targetSinPosition.x > shipPosition.x && targetSin <= shipSin)
			{
				if (distance < 125)
				{
					rotateTo(-1 * getSpeed());
				}
				else
				{
					rotateTo(1 * getSpeed());
				}
				onRightSide = true;
			}
			else if (targetSinPosition.x > shipPosition.x && targetSin > shipSin)
			{
				if (distance < 125)
				{
					rotateTo(1 * getSpeed());
				}
				else
				{
					rotateTo(-1 * getSpeed());
				}
				onRightSide = false;
			}
			else if (targetSinPosition.x < shipPosition.x)
			{
				if (targetSin >= shipSin * -1)
				{
					if (distance < 125)
					{
						rotateTo(1 * getSpeed());
					}
					else
					{
						rotateTo(-1 * getSpeed());
					}
					onRightSide = false;
				}
				else if (targetSin < shipSin * -1)
				{
					if (distance < 125)
					{
						rotateTo(-1 * getSpeed());
					}
					else
					{
						rotateTo(1 * getSpeed());
					}
					onRightSide = true;
				}
			}
		}
		else if (rotation < 270 && rotation > 90)
		{
			if (targetSinPosition.x < shipPosition.x && targetSin >= shipSin)
			{
				if (distance < 125)
				{
					rotateTo(-1 * getSpeed());
				}
				else
				{
					rotateTo(1 * getSpeed());
				}
				onRightSide = true;
			}
			else if (targetSinPosition.x < shipPosition.x && targetSin < shipSin)
			{
				if (distance < 125)
				{
					rotateTo(1 * getSpeed());
				}
				else
				{
					rotateTo(-1 * getSpeed());
				}
				onRightSide = false;
			}
			else if (targetSinPosition.x > shipPosition.x)
			{
				if (targetSin >= shipSin * -1)
				{
					if (distance < 125)
					{
						rotateTo(-1 * getSpeed());
					}
					else
					{
						rotateTo(1 * getSpeed());
					}
					onRightSide = true;
				}
				else if (targetSin < shipSin * -1)
				{
					if (distance < 125)
					{
						rotateTo(1 * getSpeed());
					}
					else
					{
						rotateTo(-1 * getSpeed());
					}
					onRightSide = false;
				}
			}
		}

		if (targetTan - shipTan <= 0.5 && targetTan - shipTan >= -0.5 && distance <= 125)
		{
			if (onRightSide)
			{
				fireRight();
			}
			else
			{
				fireLeft();
			}
		}
	}

	//swap sprite by rotation
#pragma region SpriteSwap

	float shipRotation = getShipRotation();
	float spriteAngles = (360 / 32);

	if (shipRotation > 360 - spriteAngles || shipRotation <= spriteAngles)
	{
		showShipSprite(getShipType(), 0);
	}
	else if (shipRotation > spriteAngles && shipRotation <= spriteAngles * 2)
	{
		showShipSprite(getShipType(), 1);
	}
	else if (shipRotation > spriteAngles * 2 && shipRotation <= spriteAngles * 3)
	{
		showShipSprite(getShipType(), 2);
	}
	else if (shipRotation > spriteAngles * 3 && shipRotation <= spriteAngles * 4)
	{
		showShipSprite(getShipType(), 3);
	}
	else if (shipRotation > spriteAngles * 4 && shipRotation <= spriteAngles * 5)
	{
		showShipSprite(getShipType(), 4);
	}
	else if (shipRotation > spriteAngles * 5 && shipRotation <= spriteAngles * 6)
	{
		showShipSprite(getShipType(), 5);
	}
	else if (shipRotation > spriteAngles * 6 && shipRotation <= spriteAngles * 7)
	{
		showShipSprite(getShipType(), 6);
	}
	else if (shipRotation > spriteAngles * 7 && shipRotation <= spriteAngles * 8)
	{
		showShipSprite(getShipType(), 7);
	}
	else if (shipRotation > spriteAngles * 8 && shipRotation <= spriteAngles * 9)
	{
		showShipSprite(getShipType(), 8);
	}
	else if (shipRotation > spriteAngles * 9 && shipRotation <= spriteAngles * 10)
	{
		showShipSprite(getShipType(), 9);
	}
	else if (shipRotation > spriteAngles * 10 && shipRotation <= spriteAngles * 11)
	{
		showShipSprite(getShipType(), 10);
	}
	else if (shipRotation > spriteAngles * 11 && shipRotation <= spriteAngles * 12)
	{
		showShipSprite(getShipType(), 11);
	}
	else if (shipRotation > spriteAngles * 12 && shipRotation <= spriteAngles * 13)
	{
		showShipSprite(getShipType(), 12);
	}
	else if (shipRotation > spriteAngles * 13 && shipRotation <= spriteAngles * 14)
	{
		showShipSprite(getShipType(), 13);
	}
	else if (shipRotation > spriteAngles * 14 && shipRotation <= spriteAngles * 15)
	{
		showShipSprite(getShipType(), 14);
	}
	else if (shipRotation > spriteAngles * 15 && shipRotation <= spriteAngles * 16)
	{
		showShipSprite(getShipType(), 15);
	}
	else if (shipRotation > spriteAngles * 16 && shipRotation <= spriteAngles * 17)
	{
		showShipSprite(getShipType(), 16);
	}
	else if (shipRotation > spriteAngles * 17 && shipRotation <= spriteAngles * 18)
	{
		showShipSprite(getShipType(), 17);
	}
	else if (shipRotation > spriteAngles * 18 && shipRotation <= spriteAngles * 19)
	{
		showShipSprite(getShipType(), 18);
	}
	else if (shipRotation > spriteAngles * 19 && shipRotation <= spriteAngles * 20)
	{
		showShipSprite(getShipType(), 19);
	}
	else if (shipRotation > spriteAngles * 20 && shipRotation <= spriteAngles * 21)
	{
		showShipSprite(getShipType(), 20);
	}
	else if (shipRotation > spriteAngles * 21 && shipRotation <= spriteAngles * 22)
	{
		showShipSprite(getShipType(), 21);
	}
	else if (shipRotation > spriteAngles * 22 && shipRotation <= spriteAngles * 23)
	{
		showShipSprite(getShipType(), 22);
	}
	else if (shipRotation > spriteAngles * 23 && shipRotation <= spriteAngles * 24)
	{
		showShipSprite(getShipType(), 23);
	}
	else if (shipRotation > spriteAngles * 24 && shipRotation <= spriteAngles * 25)
	{
		showShipSprite(getShipType(), 24);
	}
	else if (shipRotation > spriteAngles * 25 && shipRotation <= spriteAngles * 26)
	{
		showShipSprite(getShipType(), 25);
	}
	else if (shipRotation > spriteAngles * 26 && shipRotation <= spriteAngles * 27)
	{
		showShipSprite(getShipType(), 26);
	}
	else if (shipRotation > spriteAngles * 27 && shipRotation <= spriteAngles * 28)
	{
		showShipSprite(getShipType(), 27);
	}
	else if (shipRotation > spriteAngles * 28 && shipRotation <= spriteAngles * 29)
	{
		showShipSprite(getShipType(), 28);
	}
	else if (shipRotation > spriteAngles * 29 && shipRotation <= spriteAngles * 30)
	{
		showShipSprite(getShipType(), 29);
	}
	else if (shipRotation > spriteAngles * 30 && shipRotation <= spriteAngles * 31)
	{
		showShipSprite(getShipType(), 30);
	}
	else if (shipRotation > spriteAngles * 31 && shipRotation <= spriteAngles * 32)
	{
		showShipSprite(getShipType(), 31);
	}

#pragma endregion

	moveShip(getShipType(), cos(getShipRotation() * 3.14 / 180.0), sin(getShipRotation() * 3.14 / 180.0), getSpeed(), window);
}

void Ship::drawOut(sf::RenderWindow& window)
{
	if (!getDead())
	{
		window.draw(*this);
	}
	if (hasShootLeft)
	{
		for (int i = 0; i < 3; i++)
		{
			window.draw(bulletLeft[i]);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (bulletLeft[i].getHitShip() && bulletLeft[i].getExplotion()->getIsplaying())
		{
			window.draw(*bulletLeft[i].getExplotion());
		}
	}

	if (hasShootRight)
	{
		for (int i = 0; i < 3; i++)
		{
			window.draw(bulletRight[i]);
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (bulletRight[i].getHitShip() && bulletRight[i].getExplotion()->getIsplaying())
		{
			window.draw(*bulletRight[i].getExplotion());
		}
	}
}

Bullet* Ship::getBulletLeft(int index) const
{
	return &bulletLeft[index];
}

Bullet* Ship::getBulletRight(int index) const
{
	return &bulletRight[index];
}
