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