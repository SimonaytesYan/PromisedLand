#include <chrono>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Field/Field.h"
#include "Field/Fields.h"
#include "Window.h"
#include "WindowManager.h"
#include "RenderTarget.h"
#include "ResourcesManager.h"
#include "TextView/TextView.hpp"
#include "TextView/ResourceBar.hpp"
#include "BuildManager/BuildMenu.h"

const char* kWindowHeader  = "Promised Lands";
const int   kControlPanelH = 150;
const int   kControlPanelW = 150;
const int   kTextSize      = 20;
const int   kMSInClock     = 1000;

const std::function<Field*(int, int)> kFieldGenerators[] = 
{
	[](int x, int y) { return new Grass   (x, y); },
	[](int x, int y) { return new Windmill(x, y); },
	[](int x, int y) { return new Well    (x, y); },
	[](int x, int y) { return new Sawmill (x, y); },
	[](int x, int y) { return new House   (x, y); } 
};

void generateField(ResourcesManager& resource_man, const sf::Vector2u window_size)
{
	// leave space for controls below
	const int x_cell_cnt = (window_size.x - kControlPanelW) / kFieldSize;
	const int y_cell_cnt = (window_size.y - kControlPanelH) / kFieldSize;

	const int field_cnt = sizeof(kFieldGenerators) / sizeof(kFieldGenerators[0]);

	for (int i = 0; i <= x_cell_cnt; ++i) 
	{
		for (int j = 0; j <= y_cell_cnt; ++j) 
		{
			const int cell_x    = i * kFieldSize;
			const int cell_y    = j * kFieldSize;
			Field* cell = new Grass(cell_x, cell_y);  // kFieldGenerators[cell_type](cell_x, cell_y);
			
			resource_man.addField(static_cast<Field*>(cell));
		}
	}
}

void createInfoPanel(Window& window, ResourcesManager& resource_manager, const sf::Vector2u window_size)
{
	ResourceBar* resource_bar = new ResourceBar(window_size.x, window_size.y - kControlPanelH / 2, resource_manager);
	window.addChild(resource_bar);
}

int main()
{
	srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(), 
                            kWindowHeader, sf::Style::Fullscreen);
	RenderTarget main_rt(window.getSize().x, window.getSize().y);

	Window 	         game_window;
	WindowManger     window_manager(game_window);
	BuildingManager  build_manager;
	ResourcesManager resource_manager(kStartResources, &build_manager);

	generateField(resource_manager, window.getSize());
	game_window.addChild(&resource_manager);

	createInfoPanel(game_window, resource_manager, window.getSize());	
	game_window.addChild(new BuildMenu(window.getSize().x - kControlPanelW / 2, 100, &build_manager));


	auto timer_start = std::chrono::system_clock::now(); 
    while (window.isOpen())
	{
		// TODO: switch to EventManager
		auto timer_end = std::chrono::system_clock::now();
        auto passed   = std::chrono::duration_cast<std::chrono::milliseconds>(timer_end - timer_start);
		if (passed.count() >= kMSInClock)
		{
			window_manager.getWindow().onTick();
			resource_manager.onTick();

			timer_start = timer_end;
		}

		if (!resource_manager.isAlive())
		{
			window.close();
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
					printf("=======================================\n");
					game_window.onClick(event.mouseButton.x, event.mouseButton.y);
				}
			}
		}

		main_rt.clear();
		window.clear();
		
		window_manager.getWindow().draw(main_rt);

		main_rt.display(window);
		window .display();
    }
}