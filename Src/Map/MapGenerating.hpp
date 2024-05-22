#pragma once

#include "MapSaveLoad.hpp"
#include "../Constants.hpp"
#include "../Interlayers/CellInterlayer.hpp"

const double kDfsRiverCoef               = 0.999;
const double kIslandsFrequencyOccurrence = 0.1;
const double kDfsForestCoef              = 0.5;

const Point kTransition[] = {{ 1,  0}, 
                             {-1,  0}, 
                             { 0,  1}, 
                             { 0, -1}};

void dfsGenerating(std::vector<std::vector<FieldType>>& field, 
                   const FieldType field_type,
                   const int x, const int y, const double generate_chance);
bool dfsRiverGeneration(std::vector<std::vector<FieldType>>& field,
                        const int x, const int y, const size_t prev_index);
void generateRiver(std::vector<std::vector<FieldType>>& field);
void generateForest(std::vector<std::vector<FieldType>>& field);
void generateField(CellInterlayer& cell_int);

void generateField(CellInterlayer& cell_int)
{
    srand(time(NULL));

    std::vector<std::vector<FieldType>> field(kFieldSizeX + 1, 
                                              std::vector<FieldType>(kFieldSizeY + 1, 
                                                                     static_cast<size_t>(ReservedTypes::GRASS)));
    
    generateRiver(field);
    generateForest(field);

	for (int i = 0; i <= kFieldSizeX; ++i) 
	{
		for (int j = 0; j <= kFieldSizeY; ++j) 
		{
			const int cell_x = i * kCellSize;
			const int cell_y = j * kCellSize;

			cell_int.createCell(field[i][j], {cell_x, cell_y});
		}
	};
}

void generateRiver(std::vector<std::vector<FieldType>>& field)
{
    int start_x = getRandFromInterval(1, field[0].size()/10);
    int start_y = getRandFromInterval(1, field.size());
    for (int x = 0; x < start_x; x++)
    {
        field[start_y][x] = static_cast<size_t>(ReservedTypes::WATER);
        if (start_y + 1 < field.size())
            field[start_y + 1][x] = static_cast<size_t>(ReservedTypes::WATER);
        if (start_y > 0)
            field[start_y - 1][x] = static_cast<size_t>(ReservedTypes::WATER);
        
    }
    
    start_x = getRandFromInterval(1, field[0].size());
    start_y = getRandFromInterval(1, field.size()/10);
    for (int y = 0; y < start_y; y++)
    {
        field[y][start_x] = static_cast<size_t>(ReservedTypes::WATER);
        if (start_x + 1 < field[0].size())
            field[y][start_x + 1] = static_cast<size_t>(ReservedTypes::WATER);
        if (start_x > 0)
            field[y][start_x - 1] = static_cast<size_t>(ReservedTypes::WATER);
        
    }

    dfsRiverGeneration(field, start_x, start_y, -1);

    const size_t field_y_size = field.size(); 
    const size_t field_x_size = field[0].size();

    for (size_t i = 0; i < field_y_size; i++)
    {
        for (size_t j = 0; j < field_x_size; j++)
        {
            if (field[i][j] == static_cast<size_t>(ReservedTypes::WATER))
            {
                if (bernoulliTrial(kIslandsFrequencyOccurrence))
                    field[i][j] = static_cast<size_t>(ReservedTypes::ISLAND);
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

    while(field[y_start][x_start] != static_cast<size_t>(ReservedTypes::GRASS))
    { 
        x_start++;
        if (x_start == field[0].size())
        {
            x_start = 0;
            y_start++;
            if (y_start == field.size())
                y_start = 0;
        }
    }

    dfsGenerating(field, static_cast<size_t>(ReservedTypes::FOREST), x_start, y_start, kDfsForestCoef);
}

void dfsGenerating(std::vector<std::vector<FieldType>>& field, 
                   const FieldType field_type,
                   const int x, const int y, const double generate_chance)
{
    if (field.size() == 0)
        return;

    if (x < 0 || field[0].size() <= x)
        return;
    if (y < 0 || field.size() <= y)
        return;

    if (field[y][x] != static_cast<size_t>(ReservedTypes::GRASS))
        return;
    field[y][x] = field_type;

    for (size_t i = 0; i < sizeof(kTransition) / sizeof(kTransition[0]); i++)
    {
        if (bernoulliTrial(generate_chance))
        {
            dfsGenerating(field, field_type,
                          x + kTransition[i].x, y + kTransition[i].y,
                          generate_chance);
        }
    }
}

// return should we continue generation or not
bool dfsRiverGeneration(std::vector<std::vector<FieldType>>& field,
                        const int x, const int y, 
                        const size_t prev_index)
{
    if (field.size() == 0)
        return false;

    if (x < 0 || field[0].size() <= x)
        return true;

    if (y < 0 || field.size() <= y)
        return true;
    

    bool continue_gen = false;
    do 
    {
        if (!bernoulliTrial(kDfsRiverCoef))
            break;
        
        const size_t trans_number = sizeof(kTransition) / sizeof(kTransition[0]);
        size_t trans_index = getRandFromInterval(0, trans_number);
        if (prev_index != -1 && 
            kTransition[trans_index].x == -kTransition[prev_index].x && 
            kTransition[trans_index].y == -kTransition[prev_index].y)
            trans_index = (trans_index + 1) % trans_number;

        continue_gen = dfsRiverGeneration(field, x + kTransition[trans_index].x, 
                                          y + kTransition[trans_index].y, trans_index);
    }
    while (continue_gen);

    field[y][x] = static_cast<size_t>(ReservedTypes::WATER);
    if (x + 1 < field[0].size())
        field[y][x + 1] = static_cast<size_t>(ReservedTypes::WATER);
    if (x > 0)
        field[y][x - 1] = static_cast<size_t>(ReservedTypes::WATER);

    return false;
}

