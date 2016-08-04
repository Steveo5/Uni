#include "Grid.h"
#include <iostream>

Grid::Grid(int height)
{
	tileSize = height / vTileCount;
}

sf::Vector2f Grid::getTileAt(sf::Vector2f loc)
{
	sf::Vector2f tile(0.f, 0.f);
	tile.x = loc.x - int(loc.x) % 20;
	tile.y = loc.y - int(loc.y) % 20;
	return tile;
}

int Grid::getTileSize()
{
	return tileSize;
}

/*
Hopefully will be able to condense this method down a little in the future.
For now it works though :D
*/
void Grid::draw(sf::RenderWindow &window)
{
	//Draw the horizontal lines
	for (int i = 0; i < window.getSize().x; i+=20)
	{
		sf::Vertex line[] =
		{
			//getTileAt(sf::Vector2f(i, window.getSize().y))
			sf::Vertex(sf::Vector2f(i, 0), gridColor),
			sf::Vertex(sf::Vector2f(i, window.getSize().y), gridColor)
		};

		window.draw(line, 2, sf::Lines);
	}
	//Draw the vertical lines
	for (int i = 0; i < window.getSize().y; i += 20)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(0.f, i), gridColor),
			sf::Vertex(sf::Vector2f(window.getSize().x, i), gridColor)
		};

		window.draw(line, 2, sf::Lines);
	}
}