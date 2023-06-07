#include "Explotion.h"

void Explotion::spawn(int x, int y)
{
	setPosition(x, y);
	setIntRect(0, 0);
	isplaying = true;
	finnish = false;
	currentCounter = 0;
}

void Explotion::play()
{
	if (!finnish)
	{
		currentCounter++;
		if (currentCounter >= counter)
		{
			currentCounter = 0;
			if (getIntRectTop() == 0)
			{
				if (getIntRectLeft() == 0)
				{
					setIntRect(0, getAnimTextureSize().x / 5);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5)
				{
					setIntRect(0, getAnimTextureSize().x / 5 * 2);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 2)
				{
					setIntRect(0, getAnimTextureSize().x / 5 * 3);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 3)
				{
					setIntRect(0, getAnimTextureSize().x / 5 * 4);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 4)
				{
					setIntRect(getAnimTextureSize().y / 7, 0);
				}
			}
			else if (getIntRectTop() == getAnimTextureSize().y / 7)
			{
				if (getIntRectLeft() == 0)
				{
					setIntRect(getAnimTextureSize().y / 7, getAnimTextureSize().x / 5);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5)
				{
					setIntRect(getAnimTextureSize().y / 7, getAnimTextureSize().x / 5 * 2);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 2)
				{
					setIntRect(getAnimTextureSize().y / 7, getAnimTextureSize().x / 5 * 3);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 3)
				{
					setIntRect(getAnimTextureSize().y / 7, getAnimTextureSize().x / 5 * 4);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 4)
				{
					setIntRect(getAnimTextureSize().y * 2 / 7, 0);
				}

			}
			else if (getIntRectTop() == getAnimTextureSize().y / 7 * 2)
			{
				if (getIntRectLeft() == 0)
				{
					setIntRect(getAnimTextureSize().y / 7 * 2, getAnimTextureSize().x / 5);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5)
				{
					setIntRect(getAnimTextureSize().y / 7 * 2, getAnimTextureSize().x / 5 * 2);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 2)
				{
					setIntRect(getAnimTextureSize().y / 7 * 2, getAnimTextureSize().x / 5 * 3);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 3)
				{
					setIntRect(getAnimTextureSize().y / 7 * 2, getAnimTextureSize().x / 5 * 4);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 4)
				{
					setIntRect(getAnimTextureSize().y * 3 / 7, 0);
				}
			}
			else if (getIntRectTop() == getAnimTextureSize().y / 7 * 3)
			{
				if (getIntRectLeft() == 0)
				{
					setIntRect(getAnimTextureSize().y / 7 * 3, getAnimTextureSize().x / 5);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5)
				{
					setIntRect(getAnimTextureSize().y / 7 * 3, getAnimTextureSize().x / 5 * 2);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 2)
				{
					setIntRect(getAnimTextureSize().y / 7 * 3, getAnimTextureSize().x / 5 * 3);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 3)
				{
					setIntRect(getAnimTextureSize().y / 7 * 3, getAnimTextureSize().x / 5 * 4);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 4)
				{
					setIntRect(getAnimTextureSize().y * 4, 0);
				}
			}
			else if (getIntRectTop() == getAnimTextureSize().y / 7 * 4)
			{
				if (getIntRectLeft() == 0)
				{
					setIntRect(getAnimTextureSize().y / 7 * 4, getAnimTextureSize().x / 5);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5)
				{
					setIntRect(getAnimTextureSize().y / 7 * 4, getAnimTextureSize().x / 5 * 2);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 2)
				{
					setIntRect(getAnimTextureSize().y / 7 * 4, getAnimTextureSize().x / 5 * 3);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 3)
				{
					setIntRect(getAnimTextureSize().y / 7 * 4, getAnimTextureSize().x / 5 * 4);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 4)
				{
					setIntRect(getAnimTextureSize().y * 5, 0);
				}
			}
			else if (getIntRectTop() == getAnimTextureSize().y / 7 * 5)
			{
				if (getIntRectLeft() == 0)
				{
					setIntRect(getAnimTextureSize().y / 7 * 5, getAnimTextureSize().x / 5);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5)
				{
					setIntRect(getAnimTextureSize().y / 7 * 5, getAnimTextureSize().x / 5 * 2);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 2)
				{
					setIntRect(getAnimTextureSize().y / 7 * 5, getAnimTextureSize().x / 5 * 3);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 3)
				{
					setIntRect(getAnimTextureSize().y / 7 * 5, getAnimTextureSize().x / 5 * 4);
				}
				else if (getIntRectLeft() == getAnimTextureSize().x / 5 * 4)
				{
					setIntRect(getAnimTextureSize().y * 6, 0);
				}
			}
			else if (getIntRectTop() == getAnimTextureSize().y / 7 * 6)
			{
				if (getIntRectLeft() == 0)
				{
					setIntRect(0, 0);
					finnish = true;
					isplaying = false;
					setPosition(-1000, -1000);
				}
			}
		}
	}
}

bool Explotion::getIsplaying() const
{
	return isplaying;
}

bool Explotion::getFinnish() const
{
	return finnish;
}

Explotion::Explotion()
	:Entity("", false, false, true),
	isplaying(false),
	finnish(true),
	counter(3),
	currentCounter(0)
{

}

Explotion::~Explotion()
{

}
