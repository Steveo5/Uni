#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Snake
{

private:
	sf::Clock clock;

	std::vector<sf::CircleShape> snake;
	int direction = 2;

public:

	Snake(int playerNum);
	
	void update(sf::Time deltaTime);
	void updateMovement(sf::Keyboard::Key key, bool isPressed);

	std::vector<sf::CircleShape> getBody();


};

