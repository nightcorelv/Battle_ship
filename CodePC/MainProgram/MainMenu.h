#pragma once
#include"GameState.h"
#include"Background.h"
#include"UiButton.h"
#include"SaveLoad.h"

class MainMenu :public GameState
{
private:

	sf::Text alternatives[3];
	sf::Font font;

	Background background;
	UiButton buttons[3]
	{ 
		UiButton("../Images/UI/Button/off/000.png","../Images/UI/Button/on/000.png",1095, 293), 
		UiButton("../Images/UI/Button/off/000.png","../Images/UI/Button/on/000.png",1095, 443),
		UiButton("../Images/UI/Button/off/000.png","../Images/UI/Button/on/000.png",1095, 593)
	};

public:
	MainMenu();
	virtual ~MainMenu();

	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;
};
