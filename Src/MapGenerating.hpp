#pragma once

#include "Constants.hpp"
#include "Interlayers/CellInterlayer.hpp"

const double kDfsCoef = 0.9;

const Point kTransition[] = {{ 1,  0}, 
                             {-1,  0}, 
                             { 0,  1}, 
                             { 0, -1}};

void dfsRiver(std::vector<std::vector<FieldType>>& field, 
              const int x, const int y, const double generate_chance);
void generateRiver(std::vector<std::vector<FieldType>>& field);
void generateField(CellInterlayer& cell_int, const sf::Vector2u window_size);

void generateField(CellInterlayer& cell_int, const sf::Vector2u window_size)
{
    srand(time(NULL));

	// leave space for controls below
	const int x_cell_cnt = (window_size.x - kControlPanelW) / kFieldSize;
	const int y_cell_cnt = (window_size.y - kControlPanelH) / kFieldSize;

    std::vector<std::vector<FieldType>> field(x_cell_cnt + 1, std::vector<FieldType>(y_cell_cnt + 1));

    generateRiver(field);

	for (int i = 0; i <= x_cell_cnt; ++i) 
	{
		for (int j = 0; j <= y_cell_cnt; ++j) 
		{
			const int cell_x = i * kFieldSize;
			const int cell_y = j * kFieldSize;

			cell_int.createCell(field[i][j], {cell_x, cell_y});
		}
	}
}

void generateRiver(std::vector<std::vector<FieldType>>& field)
{
    dfsRiver(field, 0, getRandFromInterval(1, field.size()), kDfsCoef);
}

void dfsRiver(std::vector<std::vector<FieldType>>& field, 
              const int x, const int y, const double generate_chance)
{
    if (field.size() == 0)
        return;
    if (generate_chance < 0.1)
        return;

    if (x < 0 || field[0].size() <= x)
        return;
    if (y < 0 || field.size() <= y)
        return;

    field[y][x] = FieldType::Water;

    for (size_t i = 0; i < sizeof(kTransition) / sizeof(kTransition[0]); i++)
    {
        if (bernoulliTrial(generate_chance))
        {
            fprintf(stderr, "");
            dfsRiver(field, x + kTransition[i].x, y + kTransition[i].y, 
                     generate_chance * kDfsCoef);
        }
    }
}