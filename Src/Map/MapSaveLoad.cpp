#include <cstdlib>

#include "MapSaveLoad.hpp"
#include "../../JitCompiler/Src/Translation/Translation.h"
#include "../../JitCompiler/Src/Filework.h"
#include "../Constants.hpp"
#include "../Graphics/CellView/CellView.hpp"
#include "../Interlayers/CellInterlayer.hpp"
#include "../Managers/CellManager.hpp"

const size_t kMaxCompileCommandSize = 255;
const char*  command_prototype = "cd JitCompiler && make run_lang FILE=\"../%s\"";

std::vector<std::vector<FieldType>> field;
Resources 							start_resources;

static std::vector<std::vector<FieldType>> RunMapGenScript(const char* script_filepath);
static void 							   RunScript(const char* script_file);

void MapSaverLoader::loadMapFromFile(CellInterlayer& cell_int, ResourceManager& res_man, const char* map_filepath)
{
    std::vector<std::vector<FieldType>> field = RunMapGenScript(map_filepath);
 
	for (int i = 0; i <= kFieldSizeX; ++i) 
	{
		for (int j = 0; j <= kFieldSizeY; ++j) 
		{
			const int cell_x = i * kCellSize;
			const int cell_y = j * kCellSize;

			cell_int.createCell(field[i][j], {cell_x, cell_y});
		}
	}

	res_man.setResources(start_resources);

	const size_t cells_number = cell_int.cell_manager.cells.size();

	size_t house_number = 0;
	for (size_t i = 0; i < cells_number; i++)
	{
		if ((size_t)cell_int.cell_manager.cells[i]->getFieldType() == (size_t)ReservedTypes::HOUSE)
			house_number++;
	}

	const size_t population_per_house = res_man.getUserRes().population / house_number;
	size_t population_remainder = res_man.getUserRes().population % house_number;
	if (res_man.getUserRes().population != 0)
	{
		for (size_t i = 0; i < cells_number; i++)
		{
			if ((size_t)cell_int.cell_manager.cells[i]->getFieldType() == (size_t)ReservedTypes::HOUSE)
			{
				if (population_remainder > 0)
				{
					house.setPopulation(population_per_house + 1);
					population_remainder--;
				}
				else
					house.setPopulation(population_per_house);
			}
		}
	}
}

void MapSaverLoader::saveMapToFile(CellInterlayer& cell_int, const char* map_filepath)
{
	FILE* map_fp = fopen(map_filepath, "w");

	if (map_fp == nullptr)
	{
		printf("Error during file open\n");
		return;
	}

	fprintf(map_fp, "begin\n");

	const size_t cell_n = cell_int.cell_view_group->cell_views.size();
	for(size_t index = 0; index < cell_n; index++)
	{
		const Point 	pos 	   = cell_int.cell_view_group->cell_views[index]->getPos();
		const FieldType field_type = cell_int.cell_manager.cells[index]->getFieldType();
		if (field_type != 0)
			fprintf(map_fp, "\tcall build_cell(%zu, %g, %g);\n", field_type,
															   pos.x / kCellSize, 
															   pos.y / kCellSize);
	}

	fprintf(map_fp, "end\n");
	fclose(map_fp);
}


static std::vector<std::vector<FieldType>> RunMapGenScript(const char* script_filepath)
{
	field = std::vector<std::vector<FieldType>>(kFieldSizeX + 1, std::vector<FieldType>(kFieldSizeY + 1, 0));
	RunScript(script_filepath);

	return field;
}

void BuildCellImplementation(long long field_type, long long x, long long y)
{
	// printf("BuildCellImplementation(%lld, %lld, %lld)\n", field_type, x, y);
	field[x][y] = field_type;
}

long long GetCellImplementation(long long x, long long y)
{
	// printf("GetCellImplementation(%lld, %lld) = %lld\n", x, y, field[x][y]);
	return field[x][y];
}

void LoadResourcesImplementation(long long food, long long water, long long wood, 
								 long long population, long long free_population, 
								 long long stone)
{
	start_resources = Resources(food, water, wood, population, free_population, stone);
}

static void RunScript(const char* script_file)
{
	// Compile script into virtual machine executable file
	char compile_command[kMaxCompileCommandSize] = {};
	sprintf(compile_command, command_prototype, script_file);
	
    printf("compile_command = %s\n", compile_command);
    system(compile_command);

	// Jit compile + Run
	const char binary_file[] = "JitCompiler/Src/MyLanguage/Libs/CPU/a.sy";
	const size_t file_size = GetFileSize(binary_file);
	
	FILE* binary_fp = fopen(binary_file, "r");
	MyHeader binary_header = {};
    if (CheckMyHeaderFromFile(&binary_header, binary_fp) != 0)
	{
		printf("Correct binary file didn`t create\n");
		return;
	}

	TranslateAndRun(binary_file, file_size, binary_header, BuildCellImplementation, GetCellImplementation);	
}
