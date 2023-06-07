#pragma once
#include"BattleShip.h"

class ShipStats:public BattleShip
{
private:
	float currentLife;
	bool dead;

public:
	float getCurrentLife()const;
	void setCurrentLife(float value);

	bool getDead() const;
	void setDead(bool value);

	ShipStats(ShipType type);
	virtual ~ShipStats();
};

