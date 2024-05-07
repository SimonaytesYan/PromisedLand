#include <dlfcn.h>
#include <chrono>
#include <filesystem>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Graphics/Widget/BuildingPanel.hpp"
#include "Interlayers/CellInterlayer.hpp"
#include "Graphics/Widget/CellViewGroup.hpp"
#include "Constants.hpp"
#include "Utils/RenderTarget.hpp"
#include "Graphics/Widget/Window.hpp"
#include "Map/MapGenerating.hpp"
#include "Map/MapSaveLoad.hpp"
#include "../Standart/Plugin.hpp"

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

void runGameCycle(sf::RenderWindow& window, RenderTarget& rt) 
{
	Window game_window({0, 0}, "Assets/Background.png");

	ResourceBar* res_bar = new ResourceBar(window.getSize().x, window.getSize().y - kControlPanelH / 2, kStartResources);
	game_window.addChild(res_bar);

	CellViewGroup* cell_view_group = new CellViewGroup({0, 0});
	game_window.addChild(cell_view_group);

	// Interlayer + Manager initialisation
	ResourceBarInterlayer   res_bar_inter       (*res_bar);
	ResourceManager         res_manager         (res_bar_inter);
	CellManager             cell_manager        (&res_manager);
	CellInterlayer          cell_interlayer     (cell_manager);
	BuildingPanelInterlayer build_pan_interlayer(cell_manager);

	BuildingPanel* build_panel = new BuildingPanel({window.getSize().x - kControlPanelW / 2, kControlPanelYStart}, build_pan_interlayer);
	game_window.addChild(build_panel);

	cell_interlayer.setCellViewGroup(cell_view_group);

	cell_manager.setCellInterlayer(&cell_interlayer);
	cell_manager.setCellType      (0);

	cell_view_group->setCellInterlayer(&cell_interlayer);

	generateField(cell_interlayer, window.getSize());

    auto timer_start = std::chrono::system_clock::now(); 
    while (window.isOpen())
	{
		auto timer_end = std::chrono::system_clock::now();
        auto passed   = std::chrono::duration_cast<std::chrono::milliseconds>(timer_end - timer_start);
		if (passed.count() >= kMSInClock)
		{
			static int tick = 0;
			game_window.push(new Event(EventType::TICK));

			timer_start = timer_end;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
				}

				case sf::Event::MouseButtonPressed:
				{
					game_window.push(new MouseClickEvent({event.mouseButton.x, event.mouseButton.y}));
				}

				case sf::Event::MouseMoved:
				{
					game_window.push(new MouseMoveEvent({event.mouseMove.x, event.mouseMove.y}));
				}
			}
		}

		if (res_manager.hasLost())
		{
			printf("You have lost!\n");
			window.close();
		}

		rt.clear();
		window.clear();

		game_window.draw(rt);
		
		rt.display(window);
		window.display();
    }
}

void CreateGameWindowAndRunGame(sf::RenderWindow& window)
{
	RenderTarget main_rt(Point(window.getSize().x, window.getSize().y));
	runGameCycle(window, main_rt);
}

void CreateMenuWindow(sf::RenderWindow& window)
{
	RenderTarget menu_rt(Point(window.getSize().x, window.getSize().y));
	Window menu_window({0, 0}, "Assets/UI/MenuBackground.pn");

	const Point button_size(400, 200);
	Point position(window.getSize().x / 2 - button_size.x / 2 - 20, 400);

	BasicFunctor* run_game_func = new Functor<sf::RenderWindow&>(CreateGameWindowAndRunGame, window);
	menu_window.addChild(new Button(position, button_size.x, button_size.y, run_game_func, "Assets/UI/PlayButton.png"));
	
	position.y += button_size.y * 1.5;
	BasicFunctor* load_game_func = new Functor<sf::RenderWindow&>(CreateGameWindowAndRunGame, window);
	menu_window.addChild(new Button(position, button_size.x, button_size.y, load_game_func, "Assets/UI/LoadButton.png"));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				{
					window.close();
				}

				case sf::Event::MouseButtonPressed:
				{
					menu_window.push(new MouseClickEvent({event.mouseButton.x, event.mouseButton.y}));
				}

				case sf::Event::MouseMoved:
				{
					menu_window.push(new MouseMoveEvent({event.mouseMove.x, event.mouseMove.y}));
				}
			}
		}

		menu_rt.clear();
		window.clear();

		menu_window.draw(menu_rt);

		menu_rt.display(window);
		window.display();
	}
}

int main()
{
	srand(time(nullptr));

	loadPlugins();

    sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);
	CreateMenuWindow(window);
	// CreateGameWindowAndRunGame(window);
	CellKeeper::destroy();
}
