#include "Bullet.h"
#include "Ship.h"


void Bullet::spawn(int x, int y)
{
	setPosition(x, y);
	hitShip = false;
}

void Bullet::move(sf::RenderWindow& window)
{
	if (!hitShip)
	{
		moveSprite(cos(shootRotation * 3.14 / 180.0), sin(shootRotation * 3.14 / 180.0), 10);
		if (sqrt(((getPosition().x - shootPosition.x) * (getPosition().x - shootPosition.x)) + ((getPosition().y - shootPosition.y) * (getPosition().y - shootPosition.y))) > 150)
		{
			setPosition(-100, -100);
		}
	}

}

Explotion* Bullet::getExplotion() const
{
	return explotion;
}

void Bullet::shoot(sf::Vector2f position, float rotation)
{
	shootPosition = position;
	shootRotation = rotation;
	spawn(position.x, position.y);
}

void Bullet::hit(Ship* ship)
{
	explotion->spawn(getPosition().x, getPosition().y);
	hitShip = true;
	setPosition(-1000, -1000);
	ship->setCurrentLife(ship->getCurrentLife() - damage);
}

bool Bullet::getHitShip() const
{
	return hitShip;
}

Bullet::Bullet()
	:Entity("", true, false, false),
	damage(8),
	hitShip(false),
	shootRotation(0),
	explotion(new Explotion())
{
	loadBulletTexture();
}

Bullet::~Bullet()
{
	delete explotion;
}
