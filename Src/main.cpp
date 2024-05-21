#include <dlfcn.h>
#include <filesystem>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "CellLoader/CellKeeper.hpp"
#include "Events/EventManager.hpp"
#include "Graphics/Widget/DumyWidget.hpp"
#include "Interlayers/CellInterlayer.hpp"
#include "Graphics/Widget/Window.hpp"
#include "../Standart/Plugin.hpp"
#include "Menu/Menu.hpp"
#include "Managers/WindowManager.hpp"
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

int main()
{
	srand(time(nullptr));

	loadPlugins();

    sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);
	RenderTarget main_rt(Point(window.getSize().x, window.getSize().y));
	
	DummyWidget   dummy_widget;
	EventManager  event_manager;
	WindowManager window_manager(event_manager, dummy_widget);
	Window* menu = CreateMenuWindow({window, main_rt, event_manager, window_manager, dummy_widget});
	window_manager.setCurWindow(menu);

	runGameCycle(window, main_rt, event_manager, window_manager, dummy_widget);
	window_manager.setCurWindow(nullptr);
	// CreateGameWindowAndRunGame(window);
	
	CellKeeper::destroy();
}
