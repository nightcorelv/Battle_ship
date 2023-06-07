#include "GameState.h"

GameState::GameState(std::string title)
	:window(sf::VideoMode(1280, 720), title,sf::Style::Close)
{
}

GameState::~GameState()
{
}
