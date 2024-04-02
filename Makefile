RELEASE_FLAGS = -O2
DEBUG_FLAGS   = -D _DEBUG -ggdb3 -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
FLAGS 		  = $(RELEASE_FLAGS)
SFML_FLAGS    = -lsfml-graphics -lsfml-window -lsfml-system
COMPILER      = g++

SRC = Src/
BIN = Bin/
OBJ = Obj/
ELF_FILE = $(BIN)run

compile: create_folders $(OBJ)RenderTarget.o $(OBJ)Utils.o $(OBJ)Window.o
	$(COMPILER) -fPIE $(FLAGS) $(SFML_FLAGS) $(SRC)main.cpp $(OBJ)RenderTarget.o $(OBJ)Window.o $(OBJ)Utils.o -o $(ELF_FILE)

$(OBJ)RenderTarget.o: $(SRC)RenderTarget.cpp
	$(COMPILER) -fPIE -c $(FLAGS) $(SRC)RenderTarget.cpp $(SFML_FLAGS) -o $(OBJ)RenderTarget.o

$(OBJ)Utils.o: $(SRC)Utils.cpp
	$(COMPILER) -fPIE -c $(FLAGS) $(SRC)Utils.cpp -o $(OBJ)Utils.o
	
$(OBJ)Window.o: $(SRC)Window.cpp
	$(COMPILER) -fPIE -c $(FLAGS) $(SRC)Window.cpp -o $(OBJ)Window.o

run:
	./$(ELF_FILE)

create_folders:
	-mkdir $(BIN)
	-mkdir $(OBJ)

clean:
	rm -r $(BIN)
	rm -r $(OBJ)