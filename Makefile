RELEASE_FLAGS = -O2 -std=c++2a
SANITIZER_FLAGS = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
DEBUG_FLAGS   = -D _DEBUG -ggdb3 -g -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
FLAGS 		  = $(DEBUG_FLAGS)
SFML_FLAGS    = -lsfml-graphics -lsfml-window -lsfml-system
COMPILER      = g++

SRC = Src/
BIN = Bin/
OBJ = Obj/

ELF_FILE = $(BIN)run
OBJECTS  = $(OBJ)RenderTarget.o $(OBJ)Utils.o $(OBJ)CellInterlayer.o $(OBJ)CellManager.o $(OBJ)CellViewGroup.o $(OBJ)CellKeeper.o $(OBJ)MapSaveLoad.o
JIT_COMPILER_OBJ = JitCompiler/Obj/Stdlib.o JitCompiler/Obj/Translation.o JitCompiler/Obj/CommandSystem.o

compile: create_folders $(OBJECTS)
	$(COMPILER) $(FLAGS) $(SFML_FLAGS) $(SRC)main.cpp $(OBJECTS) $(JIT_COMPILER_OBJ) -o $(ELF_FILE)

$(OBJ)RenderTarget.o: create_folders $(SRC)Utils/RenderTarget.cpp
	$(COMPILER) -c $(FLAGS) $(SRC)Utils/RenderTarget.cpp $(SFML_FLAGS) -o $(OBJ)RenderTarget.o

$(OBJ)Utils.o: create_folders $(SRC)Utils/Utils.cpp
	$(COMPILER) -c $(FLAGS) $(SRC)Utils/Utils.cpp -o $(OBJ)Utils.o

$(OBJ)CellInterlayer.o: create_folders $(SRC)Interlayers/CellInterlayer.cpp
	$(COMPILER) -c $(FLAGS) $(SRC)Interlayers/CellInterlayer.cpp -o $(OBJ)CellInterlayer.o

$(OBJ)CellViewGroup.o: create_folders $(SRC)Graphics/Widget/CellViewGroup.cpp
	$(COMPILER) -c $(FLAGS) $(SRC)Graphics/Widget/CellViewGroup.cpp -o $(OBJ)CellViewGroup.o

$(OBJ)CellManager.o: create_folders $(SRC)Managers/CellManager.cpp
	$(COMPILER) -c $(FLAGS) $(SRC)Managers/CellManager.cpp -o $(OBJ)CellManager.o
	
$(OBJ)CellKeeper.o: create_folders $(SRC)CellLoader/CellKeeper.cpp
	$(COMPILER) -c $(FLAGS) $(SRC)CellLoader/CellKeeper.cpp -o $(OBJ)CellKeeper.o

$(OBJ)MapSaveLoad.o: create_folders $(SRC)Map/MapSaveLoad.cpp
	cd JitCompiler && make
	echo "JitCompiler + make success"
	$(COMPILER) -c $(FLAGS) $(SRC)Map/MapSaveLoad.cpp -o $(OBJ)MapSaveLoad.o

# $(OBJ)Window.o: $(SRC)Window.cpp
# 	$(COMPILER) -fPIE -c $(FLAGS) $(SRC)Window.cpp -o $(OBJ)Window.o

update_submodules:
	git submodule update --init --recursive --remote

run:
	./$(ELF_FILE)

create_folders:
	-mkdir $(BIN)
	-mkdir $(OBJ)

clean:
	-rm -r $(BIN)
	-rm -r $(OBJ)