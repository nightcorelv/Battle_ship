#include "ShipStats.h"

float ShipStats::getCurrentLife() const
{
    return currentLife;
}

bool ShipStats::getDead() const
{
    return dead;
}

void ShipStats::setDead(bool value)
{
    dead = value;
    if (dead)
    {
        setShipPosition(-1000, -1000);
        currentLife = 0;
    }
}

void ShipStats::setCurrentLife(float value)
{
    currentLife = value;
    if (currentLife <= 0)
    {
        setDead(true);
    }
}

ShipStats::ShipStats(ShipType type)
    :BattleShip(type),
    currentLife(100),
    dead(false)
{
    currentLife = getMaxLife();
}

ShipStats::~ShipStats()
{

}
