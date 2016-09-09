#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include "Snake.h"
#include "Menu.h"
#include "Grid.h"

class Game
{
private:
	int gameState = 0;
	std::vector<Snake> snake;
	std::vector<sf::CircleShape> &food = std::vector<sf::CircleShape>();

	sf::Vector2f lastPos;

	sf::Font font;

	sf::RenderWindow mWindow;
	Menu menu;
	Grid grid;

	int playerCount = 1;

public:
	Game::Game();
	void run();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void generateFood();
	void render();
	void update(sf::Time deltaTime);
	void proccessEvents();
	void stop();
	void start(bool reset);
	bool isRunning();
	void setPlayers(int players);
	
	static bool hasGrid();
	static bool hasSound();
	static int getDifficulty();
};