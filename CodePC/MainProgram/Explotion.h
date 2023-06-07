#pragma once
#include "Entity.h"
class Explotion :public Entity
{
private:

	int counter;
	int currentCounter;
	bool isplaying;
	bool finnish;

public:

	virtual void spawn(int x, int y) override;
	void play();

	bool getIsplaying() const;
	bool getFinnish() const;

	Explotion();
	virtual ~Explotion();
};

