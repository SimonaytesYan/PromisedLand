#pragma once

#include <SFML/Graphics.hpp>

class CellInterlayer;
class ResourceManager;

class MapSaverLoader
{
public:
	static void saveMapToFile  (CellInterlayer& cell_int, ResourceManager& res_man, const char* map_filepath);
	static void loadMapFromFile(CellInterlayer& cell_int, ResourceManager& res_man, const char* map_filepath);
};

