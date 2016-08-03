#include "Grid.h"

Grid::Grid(int height)
{
	tileSize = height / vTileCount;
}

sf::Vector2f Grid::getTileAt(sf::Vector2f loc)
{
	sf::Vector2f tile(0.f, 0.f);
	tile.x = ((loc.x + tileSize / 2) / tileSize) * tileSize;
	tile.y = ((loc.y + tileSize / 2) / tileSize) * tileSize;
	return tile;
}

int Grid::getTileSize()
{
	return tileSize;
}

void Grid::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < window.getSize().x; i+=20)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(i, 0)),
			sf::Vertex(sf::Vector2f(i, window.getSize().y))
		};

		window.draw(line, 2, sf::Lines);
	}
	for (int i = 0; i < window.getSize().y; i += 20)
	{
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(0, i)),
			sf::Vertex(sf::Vector2f(window.getSize().x, i))
		};

		window.draw(line, 2, sf::Lines);
	}
}