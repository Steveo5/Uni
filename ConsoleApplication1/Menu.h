#pragma once
#include "SFML/Graphics.hpp"

class Menu
{

public:
	Menu(float width, float height);

	void Open(int windowId);
	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	bool isOpen();
	int getOpenMenu();
	void handleInput(sf::Keyboard::Key key, bool isPressed);
	int getSelectedItemIndex();
	void Close();

private:
	
	int selectItemIndex = 0;
	int openMenu = 0;

	std::vector<sf::Text> buttons[5];
	std::vector<sf::Text> headers;
	sf::Font font;
	sf::Text text;

};

