#pragma once

#include "../Interlayers/CellInterlayer.hpp"

void createFieldFromFile(CellInterlayer& cell_int, const sf::Vector2u window_size, const char* map_filepath);
