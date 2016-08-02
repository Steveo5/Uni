#include "Menu.h"
#include <iostream>

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Font/arial.ttf"))
	{

	}
	sf::Text t1,t2;
	t1.setString("Start");
	t2.setString("Options");

	buttons.push_back(t1);
	buttons.push_back(t2);

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].setFont(font);
		buttons[i].setPosition(sf::Vector2f(width / 2 - (buttons[i].getLocalBounds().width/2), height / 2 - (buttons[i].getLocalBounds().height/2 - i * 50)));
	}
}

bool Menu::isOpen()
{
	return true;
}


void Menu::Open(sf::RenderWindow &window, int windowId)
{
	

}

void Menu::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		std::cout << "test drawing" << std::endl;
		window.draw(buttons[i]);
	}
}

void Menu::MoveUp()
{

}

void Menu::MoveDown()
{

}

void Menu::handleInput(sf::Keyboard::Key key, bool isPressed)
{

}
