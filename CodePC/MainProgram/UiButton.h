#pragma once
#include"Entity.h"
#include<string>

class UiButton:public Entity
{
private:
	//on off texture
	sf::Texture* textures[2];
	bool isOn;
	bool clicked;

	//delay after click
	bool finnishDelay;
	int delayTime;

public:

	//mouse actions
	bool mouseOver(sf::RenderWindow& window) const;
	bool mouseDown(sf::RenderWindow& window) const;

	//daly to action
	bool getFinnishDelay() const;

	//set click
	void setClicked(bool value);
	//reset button
	void reset();

	//button states
	bool getIsOn() const;
	void setIsOn(bool value);

	virtual void spawn(int x, int y) override;
	void update();

	UiButton(std::string nonClick, std::string click, int x, int y);
	virtual ~UiButton();
};

