#include "Background.h"

void Background::spawn(int x, int y)
{
	setPosition(x, y);
}

Background::Background(std::string path, int x, int y)
	:Entity(path, false, false, false)
{
	spawn(x, y);
}

Background::~Background()
{

}
