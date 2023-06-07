#pragma once
#include"ShipStats.h"
#include"Bullet.h"

class Ship:public ShipStats
{
private:
	//targets and player check
	bool isPlayer;
	Ship* target;
	Ship** targets;
	int nrOfTargets;

	//bulletLeft
	float timeCountLeft;
	bool availableToFireLeft;
	bool hasShootLeft;
	Bullet* bulletLeft;

	//bulletRight
	float timeCountRight;
	bool availableToFireRight;
	bool hasShootRight;
	Bullet* bulletRight;

public:

	virtual void spawn(int x, int y) override;
	void move(sf::RenderWindow& window);

	//fire
	void fireLeft();
	void fireRight();

	//targts
	void setTarget(Ship* targetShip);
	void setTargets(Ship** targetShips,int nrOf);

	//draw ship
	void drawOut(sf::RenderWindow& window);
	//get left bullet pointer
	Bullet* getBulletLeft(int index) const;
	//get right bullet pointer
	Bullet* getBulletRight(int index) const;

	Ship();
	Ship(ShipType type, Ship* playerShip, bool isplayer);
	virtual ~Ship();
};

