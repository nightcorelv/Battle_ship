#include "UiButton.h"


bool UiButton::mouseOver(sf::RenderWindow& window) const
{
	return getBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

bool UiButton::mouseDown(sf::RenderWindow& window) const
{
	return getBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

bool UiButton::getFinnishDelay() const
{
	return finnishDelay;
}

void UiButton::setClicked(bool value)
{
	clicked = value;
}

void UiButton::reset()
{
	isOn = false;
	clicked = false;
	finnishDelay = false;
	delayTime = 0;
}

bool UiButton::getIsOn() const
{
	return isOn;
}

void UiButton::setIsOn(bool value)
{
	isOn = value;
	if (isOn)
	{
		changeTexture(textures[1]);
	}
	else
	{
		changeTexture(textures[0]);
	}
}

void UiButton::spawn(int x, int y)
{
	setPosition(x, y);
}

void UiButton::update()
{
	if (clicked)
	{
		if (++delayTime >= 10)
		{
			finnishDelay = true;
		}
	}
}

UiButton::UiButton(std::string nonClick, std::string click, int x, int y)
	:Entity("", false, false, false),
	isOn(false),
	clicked(false),
	delayTime(0),
	finnishDelay(false)
{
	textures[0] = new sf::Texture;
	textures[0]->loadFromFile(nonClick);
	changeTexture(textures[0]);

	textures[1] = new sf::Texture;
	textures[1]->loadFromFile(click);

	spawn(x, y);
}

UiButton::~UiButton()
{
	delete textures[0];
	delete textures[1];
}
