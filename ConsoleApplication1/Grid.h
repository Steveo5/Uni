#pragma once
#include <SFML/Graphics.hpp>

class Grid
{
private:
	//Count should be resolution / 2
	int vTileCount = 32;
	int hTileCount = 24;

	int tileSize = 20;

public:
	Grid(int height);
	sf::Vector2f getTileAt(sf::Vector2f loc);
	int getTileSize();
	void draw(sf::RenderWindow &window);
};

