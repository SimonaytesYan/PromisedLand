#include <cstdlib>

#include "../../JitCompiler/Src/Translation/Translation.h"
#include "../../JitCompiler/Src/Filework.h"

const size_t kMaxCompileCommandSize = 255;
const char* command_prototype = "cd JitCompiler && make run_lang FILE=\"../%s\"";

#include "../Constants.hpp"
#include "../Interlayers/CellInterlayer.hpp"

const size_t kCellFieldSize = 64;

void RunScript(const char* script_file);

std::vector<std::vector<FieldType>> field;

std::vector<std::vector<FieldType>> LoadMap(const char* file)
{
	field = std::vector<std::vector<FieldType>>(kCellFieldSize, std::vector<FieldType>(kCellFieldSize, 0));
	RunScript(file);

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

void RunScript(const char* script_file)
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
