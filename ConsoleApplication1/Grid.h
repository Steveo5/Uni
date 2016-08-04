#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
private:
	//Count should be resolution / 2
	const int vTileCount = 32;
	const int hTileCount = 24;

	int tileSize = 20;

	const sf::Color gridColor = sf::Color(31, 31, 31);

public:
	Grid(int height);
	sf::Vector2f getTileAt(sf::Vector2f loc);
	int getTileSize();
	void draw(sf::RenderWindow &window);
};

