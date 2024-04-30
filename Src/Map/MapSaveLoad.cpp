#include <cstdlib>

#include "../../JitCompiler/Src/Translation/Translation.h"
#include "../../JitCompiler/Src/Filework.h"

const size_t kMaxCompileCommandSize = 255;
const char* command_prototype = "cd JitCompiler && make run_lang FILE=\"../%s\"";

void RunScript(const char* script_file)
{
	// Compile to virtual machine
	char compile_command[kMaxCompileCommandSize] = {};
	sprintf(compile_command, command_prototype, script_file);
	
    printf("compile_command = %s\n", compile_command);
    system(compile_command);

	// Jit compile + Run
	const char binary_file[] = "JitCompiler/Src/MyLanguage/Libs/CPU/a.sy";
	const size_t file_size = GetFileSize(binary_file);
	
	FILE* binary_fp = fopen(binary_file, "-r");
	MyHeader binary_header = {};
    if (CheckMyHeaderFromFile(&binary_header, binary_fp) != 0)
	{
		printf("Not correct file ");
		return;
	}

	TranslateAndRun(binary_file, file_size, binary_header);	
}
