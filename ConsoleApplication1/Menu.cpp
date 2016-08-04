#include "Menu.h"
#include <iostream>

#define MAX_MENU_ITEMS = 5;

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Font/arial.ttf"))
	{
	}
	sf::Text t1,t2,t3;
	t1.setString("Start");
	t2.setString("Options");
	t3.setString("Quit");

	buttons[0].push_back(t1);
	buttons[0].push_back(t2);
	buttons[0].push_back(t3);

	sf::Text a1, a2, a3;
	t1.setString("Easy");
	t2.setString("Medium");
	t3.setString("Hard");

	buttons[1].push_back(a1);
	buttons[1].push_back(a2);
	buttons[1].push_back(a3);

	for (int b = 0; b < 5; b++)
	{
		for (int i = 0; i < buttons[b].size(); i++)
		{
			buttons[b][i].setFont(font);
			buttons[b][i].setPosition(sf::Vector2f(width / 2 - (buttons[b][i].getLocalBounds().width / 2), height / 2 - ((buttons[b][i].getLocalBounds().height / 2) - i * 50)));
		}
	}
	for (int i = 0; i < headers.size(); i++)
	{

	}
}

bool Menu::isOpen()
{
	return openMenu == 0;
}


void Menu::Open(int windowId)
{
	openMenu = windowId;
	selectItemIndex = 0;
}

void Menu::Close()
{
	openMenu = -1;
}

void Menu::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < buttons[getOpenMenu()].size(); i++)
	{
		sf::Text& button = buttons[getOpenMenu()][i];
		if (i == getSelectedItemIndex())
		{
			button.setColor(sf::Color::Red);
		}
		else
		{
			button.setColor(sf::Color::White);
		}
		window.draw(button);
	}
}

int Menu::getOpenMenu()
{
	return openMenu;
}

void Menu::MoveUp()
{
	selectItemIndex--;
}

void Menu::MoveDown()
{
	selectItemIndex++;
}

void Menu::handleInput(sf::Keyboard::Key key, bool isPressed)
{	
	if (isPressed)
	{
		if (key == sf::Keyboard::Key::Up)
		{
			MoveUp();
		}
		else if (key == sf::Keyboard::Key::Down)
		{
			MoveDown();
		}
		if (key == sf::Keyboard::Key::Space)
		{
			//Do the things for menu with id = 0
			if (openMenu == 0)
			{
				if (selectItemIndex == 0)
				{
					selectItemIndex = -1;
				}
			}
		}
	}
}

int Menu::getSelectedItemIndex()
{
	return selectItemIndex;
}
