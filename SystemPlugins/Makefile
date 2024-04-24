RELEASE_FLAGS = -O2 -std=c++2a
DEBUG_FLAGS   = -D _DEBUG -ggdb3 -g -std=c++2a -O0 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -Wstack-usage=8192 -pie -fPIE -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,leak,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr
FLAGS 		  = $(DEBUG_FLAGS)
SFML_FLAGS    = -lsfml-graphics -lsfml-window -lsfml-system
COMPILER      = g++
LIB_BUILDER   = gcc

NAME = Forest
LIB_PATH = ../PluginObjects/

all: create_cell_o create_view_o create_interface_o create_so rm_o

create_cell_o:
	$(COMPILER) -g -c $(FLAGS) -o $(NAME)Cell.o $(NAME)/Cell.cpp $(SFML_FLAGS) -fPIC

create_view_o:
	$(COMPILER) -g -c $(FLAGS) -o $(NAME)View.o $(NAME)/View.cpp $(SFML_FLAGS) -fPIC

create_interface_o:
	$(COMPILER) -g -c $(FLAGS) -o $(NAME)Interface.o $(NAME)/Interface.cpp $(SFML_FLAGS) -fPIC

create_so:
	$(LIB_BUILDER) -shared -o $(LIB_PATH)$(NAME).so $(NAME)Cell.o $(NAME)View.o $(NAME)Interface.o

rm_o:
	rm *.o