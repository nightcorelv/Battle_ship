#include "SaveLoad.h"

std::ifstream SaveLoad::in;
std::ofstream SaveLoad::out;

void SaveLoad::fightWith(std::string difficulty, int numberOfEnemys, int reward)
{
	out.open("../data/fight.txt");
	if (out.is_open())
	{
		out << difficulty
			<< std::endl
			<< numberOfEnemys
			<< std::endl
			<< reward;

		out.close();
	}
}

void SaveLoad::loadFightInfo(std::string& difficulty, int& numberOfEnemys, int& reward)
{
	in.open("../data/fight.txt");
	if (in.is_open())
	{
		in >> difficulty;
		in.ignore();

		in >> numberOfEnemys;
		in.ignore();

		in >> reward;

		in.close();
	}
}

void SaveLoad::save(ShipType type, int gold, float currentLife)
{
	out.open("../data/save.txt");
	if (out.is_open())
	{
		if (type == ShipType::None)
		{
			out << "None" 
				<< std::endl 
				<< gold 
				<< std::endl 
				<< currentLife 
				<< std::endl;
		}
		else if (type == ShipType::Normal_Ship)
		{
			out << "Normal"
				<< std::endl
				<< gold
				<< std::endl
				<< currentLife
				<< std::endl;
		}
		else if (type == ShipType::Speed_Ship)
		{
			out << "Speed"
				<< std::endl
				<< gold
				<< std::endl
				<< currentLife
				<< std::endl;
		}
		else if (type == ShipType::Creators_Ship)
		{
			out << "Creator"
				<< std::endl
				<< gold
				<< std::endl
				<< currentLife
				<< std::endl;
		}

		out.close();
	}
}

void SaveLoad::load(ShipType& type, int& gold, float& currentLife)
{
	std::string loadType;

	in.open("../data/save.txt");
	if (in.is_open())
	{
		std::getline(in, loadType);
		in >> gold;
		in.ignore();
		in >> currentLife;

		in.close();

		if (loadType == "None")
		{
			type = ShipType::None;
		}
		else if (loadType == "Normal")
		{
			type = ShipType::Normal_Ship;
		}
		else if (loadType == "Speed")
		{
			type = ShipType::Speed_Ship;
		}
		else if (loadType == "Creator")
		{
			type = ShipType::Creators_Ship;
		}
	}
}

SaveLoad::SaveLoad()
{

}

SaveLoad::~SaveLoad()
{

}
