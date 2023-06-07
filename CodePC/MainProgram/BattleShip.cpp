#include "BattleShip.h"

float BattleShip::getMaxLife() const
{
    return maxLife;
}

float BattleShip::getSpeed() const
{
    return speed;
}

ShipType BattleShip::getShipType() const
{
    return type;
}

void BattleShip::setShipType(ShipType type)
{
    this->type = type;
}

BattleShip::BattleShip(ShipType type)
    :Entity("../Images/Normal_Ship/right/000.png", true, true, false),
    type(type),
    maxLife(100),
    speed(0)
{
    if (type == ShipType::Normal_Ship)
    {
        maxLife = 100;
        speed = 1;
    }
    else if (type == ShipType::Speed_Ship)
    {
        maxLife = 120;
        speed = 1.1;
    }
    else if (type == ShipType::Creators_Ship)
    {
        maxLife = 150;
        speed = 1.2;
    }
}

BattleShip::~BattleShip()
{
}
