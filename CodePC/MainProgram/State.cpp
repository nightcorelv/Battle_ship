#include "Game.h"
#include "MainMenu.h"
#include "Town.h"
#include <iostream>
#include "Background.h"
#include "List.h"
#include <sstream>
#include <vector>
#include <chrono>

#include <fstream>

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#endif

class ttop
{
public:
	int oop = 99;
	ttop(){}
	ttop(int v) : oop(v){}

};

class hhop : public ttop
{
public:

	hhop() {}

};


int main()
{
	std::srand((unsigned)time(0));
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	


	hhop hhhhh;

	if(typeid(hhhhh).name() == typeid(ttop).name())
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;

	GameState* current = nullptr;
	State currentState = State::NO_CHANGE;

	current = new MainMenu();
	currentState = State::MENU;


	while (currentState != State::EXIT)
	{
		current->handleEvents();
		currentState = current->update();

		if (currentState != State::NO_CHANGE)
		{

			switch (currentState)
			{
			case State::MENU:
				delete current;
				current = new MainMenu();
				break;
			case State::TOWN:
				delete current;
				current = new Town();
				break;
			case State::FIGHT:
				delete current;
				current = new Game();
				break;
			}
		}
		current->render();
	}

	//delete static textures
	Entity::deleteStaticTextures();
	delete current;

	return 0;
}