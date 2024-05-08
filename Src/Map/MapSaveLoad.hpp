#pragma once

#include <SFML/Graphics.hpp>

class CellInterlayer;

class MapSaver
{
public:
	static void saveMapToFile(CellInterlayer& cell_int, const char* map_filepath);
};

void loadMapFromFile(CellInterlayer& cell_int, const sf::Vector2u window_size, const char* map_filepath);
