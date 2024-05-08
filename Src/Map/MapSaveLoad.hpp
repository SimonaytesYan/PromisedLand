#pragma once

#include "../Interlayers/CellInterlayer.hpp"

void loadMapFromFile(CellInterlayer& cell_int, const sf::Vector2u window_size, const char* map_filepath);

class MapSaver
{
	static void saveMapToFile(CellInterlayer& cell_int, const char* map_filepath);
}
