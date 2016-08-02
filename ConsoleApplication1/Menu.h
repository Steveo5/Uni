#pragma once
#include "SFML/Graphics.hpp"

class Menu
{
public:
	Menu(float width, float height);

	void Open(sf::RenderWindow &window, int windowId);
	void Draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	bool isOpen();
	void handleInput(sf::Keyboard::Key key, bool isPressed);

private:
	
	int selectItemIndex;
	std::vector<sf::Text> buttons;
	sf::Font font;
	sf::Text text;

};

