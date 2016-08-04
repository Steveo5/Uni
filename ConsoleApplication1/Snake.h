#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Snake
{

private:
	sf::Clock clock;

	std::vector<sf::CircleShape> snake;
	int direction = 2;

	int score = 0;
	int pNo;

public:

	Snake(int playerNum);
	
	void update(sf::Time deltaTime);
	void updateMovement(sf::Keyboard::Key key, bool isPressed);

	std::vector<sf::CircleShape> &getBody();
	void handleCollision(sf::CircleShape obj, bool isFood);

	int getScore();
	void setScore(int score);
	int getNumber();
};

