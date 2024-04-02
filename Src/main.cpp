#include <functional>

#include <SFML/Graphics.hpp>

#include "Field/Field.h"
#include "Field/Building/Windmill.h"
#include "Field/Building/Well.h"
#include "Field/Building/Sawmill.h"
#include "Field/Building/House.h"
#include "Window.h"
#include "WindowManager.h"
#include "RenderTarget.h"
#include "ResourcesManager.h"
#include "Field/Building/IncodeOutcome.h"
#include "TextView/TextView.hpp"
#include "TextView/ResourceBar.hpp"

const char* kWindowHeader  = "Promised Lands";
const int   kControlPanelH = 150;
const int   kTextSize      = 20;

const std::function<Field*(int, int)> kFieldGenerators[] = 
{
	[](int x, int y) { return new Field   (x, y); },
	[](int x, int y) { return new Windmill(x, y); },
	[](int x, int y) { return new Well    (x, y); },
	[](int x, int y) { return new Sawmill (x, y); },
	[](int x, int y) { return new House   (x, y); } 
};

void generateField(Window& window, ResourcesManager& resource_man, const sf::Vector2u window_size)
{
	// kFieldSize = radius of circle
	const int x_cell_cnt = window_size.x                    / (kFieldSize * 2);
	// leave space for controls below
	const int y_cell_cnt = (window_size.y - kControlPanelH) / (kFieldSize * 2);

	const int field_cnt = sizeof(kFieldGenerators) / sizeof(kFieldGenerators[0]);

	for (int i = 0; i <= x_cell_cnt; ++i) 
	{
		for (int j = 0; j <= y_cell_cnt; ++j) 
		{
			const int cell_x    = i * kFieldSize * 2;
			const int cell_y    = j * kFieldSize * 2;
			const int cell_type = rand() % field_cnt;
			Field* cell = kFieldGenerators[cell_type](cell_x, cell_y);

			window.addChild(cell);
			
			// TODO: make better
			if (cell_type != 0) resource_man.addBuilding(static_cast<Building*>(cell));
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
	ResourcesManager resource_manager(kStartResources);

	generateField  (game_window, resource_manager, window.getSize());
	createInfoPanel(game_window, resource_manager, window.getSize());	

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
			}
		}
		
		window_manager.getWindow().onTick();
		window_manager.getWindow().draw(main_rt);

		main_rt.display(window);
		window .display();
    }
}