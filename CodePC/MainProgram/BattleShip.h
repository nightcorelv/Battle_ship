#pragma once
#include"Entity.h"

class BattleShip: public Entity
{
private:

	ShipType type;
	float maxLife;
	float speed;

public:

	float getMaxLife()const;
	float getSpeed()const;
	ShipType getShipType()const;
	void setShipType(ShipType type);

	BattleShip(ShipType type);
	virtual ~BattleShip();
};

