#pragma once
#include "Entity.h"
class Background : public Entity
{
public:

	virtual void spawn(int x, int y) override;
	Background(std::string path, int x, int y);
	virtual ~Background();
};

