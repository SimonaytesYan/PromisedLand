#include <dlfcn.h>
#include <filesystem>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "CellLoader/CellKeeper.hpp"
#include "Interlayers/CellInterlayer.hpp"
#include "Graphics/Widget/Window.hpp"
#include "../Standart/Plugin.hpp"
#include "Menu/Menu.hpp"
#include "GameCycle/GameCycle.hpp"
#include "Utils/RenderTarget.hpp"

typedef CellInterface* (*interfaceFun)();

void loadPlugins()
{
	for (const auto& plugin_file : std::filesystem::directory_iterator(kPluginFolder))
	{
		void* interface_lib       = dlopen(plugin_file.path().c_str(), RTLD_NOW | RTLD_LOCAL | RTLD_NODELETE);
        interfaceFun get_int_func = (interfaceFun)(dlsym(interface_lib, "getCellInterface"));
        CellInterface* plugin     = get_int_func();
        dlclose(interface_lib);

        CellKeeper::add(plugin);
	}
}

// void setMapSize(const sf::Vector2u window_size) 
// {
// 	visible_part_x = (window_size.x - kControlPanelW) / kFieldSize;
// 	visible_part_y = (window_size.y - kControlPanelH) / kFieldSize;
// }

int main()
{
	srand(time(nullptr));

	loadPlugins();

	bool run_loop = true;
    sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);
	RenderTarget main_rt(Point(window.getSize().x, window.getSize().y));
	Window menu = CreateMenuWindow(window, main_rt);

	runGameCycle(window, main_rt, menu);
	// CreateGameWindowAndRunGame(window);
	CellKeeper::destroy();
}
