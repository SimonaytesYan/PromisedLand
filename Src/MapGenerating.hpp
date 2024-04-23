#pragma once

#include "Constants.hpp"
#include "Interlayers/CellInterlayer.hpp"

const double kDfsRiverCoef               = 0.9;
const double kIslandsFrequencyOccurrence = 0.1;
const double kDfsForestCoef              = 0.8;

const Point kTransition[] = {{ 1,  0}, 
                             {-1,  0}, 
                             { 0,  1}, 
                             { 0, -1}};

void dfsGenerating(std::vector<std::vector<FieldType>>& field, 
                   const FieldType field_type,
                   const int x, const int y, const double generate_chance);
void dfsRiverGeneration(std::vector<std::vector<FieldType>>& field, 
                        const FieldType field_type,
                        const int x, const int y, const double generate_chance, 
                        const size_t prev_index);
void generateRiver(std::vector<std::vector<FieldType>>& field);
void generateForest(std::vector<std::vector<FieldType>>& field);
void generateField(CellInterlayer& cell_int, const sf::Vector2u window_size);

void generateField(CellInterlayer& cell_int, const sf::Vector2u window_size)
{
    srand(time(NULL));

	// leave space for controls below
	const int x_cell_cnt = (window_size.x - kControlPanelW) / kFieldSize;
	const int y_cell_cnt = (window_size.y - kControlPanelH) / kFieldSize;

    // TODO:
    std::vector<std::vector<FieldType>> field(x_cell_cnt + 1, 
                                              std::vector<FieldType>(y_cell_cnt + 1, 
                                                                     0));

    generateRiver(field);
    generateForest(field);

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
    // TODO:
    dfsRiverGeneration(field, 1, 0, getRandFromInterval(1, field.size()), 
                       kDfsRiverCoef, -1);

    for (size_t i = 0; i < field.size(); i++)
    {
        for (size_t j = 0; j < field[i].size(); j++)
        {
            // TODO:
            if (field[i][j] == 1)
            {
                // TODO:
                if (bernoulliTrial(kIslandsFrequencyOccurrence))
                    field[i][j] = 3;
            }
        }
    }

}

void generateForest(std::vector<std::vector<FieldType>>& field)
{
    if (field.size() == 0)
        return;

    size_t y_start = getRandFromInterval(1, field.size());
    size_t x_start = getRandFromInterval(1, field[0].size());
    // TODO:
    while(field[y_start][x_start] != 0)
    { 
        y_start = getRandFromInterval(1, field.size());
        x_start = getRandFromInterval(1, field[0].size());
    }

    // TODO:
    dfsGenerating(field, 1, x_start, y_start, kDfsForestCoef);
}

void dfsGenerating(std::vector<std::vector<FieldType>>& field, 
                   const FieldType field_type,
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

    // TODO:
    if (field[y][x] != 0)
        return;
    field[y][x] = field_type;

    for (size_t i = 0; i < sizeof(kTransition) / sizeof(kTransition[0]); i++)
    {
        if (bernoulliTrial(generate_chance))
        {
            dfsGenerating(field, field_type,
                          x + kTransition[i].x, y + kTransition[i].y,
                          generate_chance * 0.95);
        }
    }
}

void dfsRiverGeneration(std::vector<std::vector<FieldType>>& field, 
                        const FieldType field_type,
                        const int x, const int y, const double generate_chance, 
                        const size_t prev_index)
{
    if (field.size() == 0)
        return;
    if (generate_chance < 0.1)
        return;

    if (x < 0 || field[0].size() <= x)
        return;
    if (y < 0 || field.size() <= y)
        return;

    // TODO: change
    if (field[y][x] != 0)
        return;
    field[y][x] = field_type;

    size_t counter = 0;
    for (size_t i = 0; i < sizeof(kTransition) / sizeof(kTransition[0]); i++)
    {
        if (prev_index == i && (bernoulliTrial(generate_chance) || bernoulliTrial(generate_chance)) || 
            (prev_index != i && bernoulliTrial(generate_chance)))
        {
            dfsRiverGeneration(field, field_type,
                               x + kTransition[i].x, y + kTransition[i].y,
                               generate_chance * 0.95, i);
            counter++;
            if (counter == 2)
                break;
        }
    }
}

