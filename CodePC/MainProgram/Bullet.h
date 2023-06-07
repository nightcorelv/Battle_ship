#pragma once
#include "Entity.h"
#include "Explotion.h"

class Ship;

class Bullet:public Entity
{
private:
	float damage;
	bool hitShip;

	Explotion* explotion;

	sf::Vector2f shootPosition;
	float shootRotation;

	virtual void spawn(int x, int y) override;

public:

	void move(sf::RenderWindow& window);
	Explotion* getExplotion() const;
	void shoot(sf::Vector2f position, float rotation);
	void hit(Ship* ship);
	bool getHitShip() const;

	Bullet();
	virtual ~Bullet();
};

