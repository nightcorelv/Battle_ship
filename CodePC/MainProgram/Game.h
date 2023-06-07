#pragma once
#include "GameState.h"
#include "ShipHandler.h"
#include "Background.h"
#include "UiButton.h"

class Game : public GameState
{
private:
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;

	bool paused;
	UiButton pauseButton = UiButton("../Images/UI/Pause/on/000.png", "../Images/UI/Pause/off/000.png", 0, 0);
	int pausedColddown;

	Background control;

	ShipHandler handler;
public:
	Game();
	virtual ~Game();

	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;

};
