#pragma once
#include <fstream>
#include"Ship.h"
#include<string>

class SaveLoad
{
private:
	static std::ifstream in;
	static std::ofstream out;

public:

	static void fightWith(std::string difficulty, int numberOfEnemys, int reward);
	static void loadFightInfo(std::string& difficulty, int& numberOfEnemys, int& reward);

	static void save(ShipType type, int gold, float currentLife);
	static void load(ShipType& type, int& gold, float& currentLife);

	SaveLoad();
	virtual ~SaveLoad();
};

