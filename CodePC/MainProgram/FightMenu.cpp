#include "FightMenu.h"

void FightMenu::draw(sf::RenderWindow& window)
{
	window.draw(background);

	window.draw(fight);
	window.draw(fightText);

	for (int i = 0; i < 4; i++)
	{
		window.draw(enemyDifficultyToggles[i]);
		window.draw(enemyDifficultyTogglesText[i]);

		window.draw(enemyNumberToggles[i]);
		window.draw(enemyNumberTogglesText[i]);
	}

}

void FightMenu::update(sf::RenderWindow& window)
{
	//click Colddown
	if (clickColddown <= 20)
	{
		clickColddown++;
	}
	//toggle click events
	for (int i = 0; i < 4; i++)
	{
		if (enemyDifficultyToggles[i].mouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clickColddown >= 20 && !enemyDifficultyToggles[i].getIsOn())
		{
			for (int k = 0; k < 4; k++)
			{
				enemyDifficultyToggles[k].setIsOn(false);
			}
			enemyDifficultyToggles[i].setIsOn(true);
			clickColddown = 0;
		}
		else if (enemyNumberToggles[i].mouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clickColddown >= 20 && !enemyNumberToggles[i].getIsOn())
		{
			for (int k = 0; k < 4; k++)
			{
				enemyNumberToggles[k].setIsOn(false);
			}
			enemyNumberToggles[i].setIsOn(true);
			clickColddown = 0;
		}
	}

	//fight button
	if (fight.mouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && clickColddown >= 20 && !fight.getIsOn())
	{
		std::string difficulty="";
		int nrOf=0;
		int reward=0;
		
		//get button index
		int difficultyIndex = -1;
		int nrOfIndex = -1;
		//loop all buttons
		for (int i = 0; i < 4; i++)
		{
			if (enemyDifficultyToggles[i].getIsOn())
			{
				difficultyIndex = i;
			}
			if (enemyNumberToggles[i].getIsOn())
			{
				nrOfIndex = i;
			}
		}
		//set string
		if (difficultyIndex == 0)
		{
			difficulty = "Easy";
		}
		else if (difficultyIndex == 1)
		{
			difficulty = "Normal";
		}
		else if (difficultyIndex == 2)
		{
			difficulty = "Hard";
		}
		else if (difficultyIndex == 3)
		{
			difficulty = "Random";
		}
		// set nrof and reward
		if (nrOfIndex == 0)
		{
			nrOf = 1;
			reward = 10000 + difficultyIndex * 0.5 * 5000;
		}
		else if (nrOfIndex == 1)
		{
			nrOf = 2;
			reward = 30000 + difficultyIndex * 0.5 * 5000;
		}
		else if (nrOfIndex == 2)
		{
			nrOf = 2;
			reward = 60000 + difficultyIndex * 0.5 * 5000;
		}
		else if (difficultyIndex == 3)
		{
			nrOf = 4;
			reward = 100000 + difficultyIndex * 0.5 * 5000;
		}

		//save to file
		SaveLoad::fightWith(difficulty, nrOf, reward);
		go = true;
	}
}

bool FightMenu::getGo() const
{
	return go;
}

FightMenu::FightMenu()
	:background(Background("../Images/UI/Market/000.png", 407, 30)) ,
	clickColddown(20),
	go(false)
{

	enemyNumberToggles[0].setIsOn(true);
	enemyDifficultyToggles[3].setIsOn(true);

	font.loadFromFile("C:/Windows/Fonts/arial.ttf");

	fightText.setFont(font);
	fightText.setFillColor(sf::Color::Blue);
	fightText.setCharacterSize(30);
	fightText.setString("Fight");
	fightText.setPosition(610, 565);

	for (int i = 0; i < 4; i++)
	{
		//text
		enemyNumberTogglesText[i].setFont(font);
		enemyDifficultyTogglesText[i].setFont(font);
		
		enemyNumberTogglesText[i].setFillColor(sf::Color::Red);
		enemyDifficultyTogglesText[i].setFillColor(sf::Color::Red);

		enemyNumberTogglesText[i].setCharacterSize(20);
		enemyDifficultyTogglesText[i].setCharacterSize(20);

		enemyNumberTogglesText[i].setOutlineThickness(2);
		enemyDifficultyTogglesText[i].setOutlineThickness(2);

		enemyNumberTogglesText[i].setPosition(500, 100 + 50 * i);
		enemyDifficultyTogglesText[i].setPosition(500, 350 + 50 * i);

		if (i == 0)
		{
			enemyNumberTogglesText[i].setString(std::to_string(i + 1) + " Enemys (10000 Golds)");
			enemyDifficultyTogglesText[i].setString("Easy");
		}
		else if (i == 1)
		{
			enemyNumberTogglesText[i].setString(std::to_string(i + 1) + " Enemys (30000 Golds)");
			enemyDifficultyTogglesText[i].setString("Normal");
		}
		else if (i == 2)
		{
			enemyNumberTogglesText[i].setString(std::to_string(i + 1) + " Enemys (60000 Golds)");
			enemyDifficultyTogglesText[i].setString("Hard");
		}
		else if (i == 3)
		{
			enemyNumberTogglesText[i].setString(std::to_string(i + 1) + " Enemys (100000 Golds)");
			enemyDifficultyTogglesText[i].setString("Random");
		}
	}

}

FightMenu::~FightMenu()
{
}
