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

const char* kWindowHeader = "Promised Lands";

const std::function<Field*(int, int)> kFieldGenerators[] = 
{
	[](int x, int y) { return new Field   (x, y); },
	[](int x, int y) { return new Windmill(x, y); },
	[](int x, int y) { return new Well    (x, y); },
	[](int x, int y) { return new Sawmill (x, y); },
	[](int x, int y) { return new House   (x, y); } 
};

void generateField(Window& window, const sf::Vector2u window_size)
{
	// kFieldSize = radius of circle
	int x_cell_cnt = window_size.x / (kFieldSize * 2);
	int y_cell_cnt = window_size.y / (kFieldSize * 2);

	int field_cnt = sizeof(kFieldGenerators) / sizeof(kFieldGenerators[0]);

	for (int i = 0; i <= x_cell_cnt; ++i) {
		for (int j = 0; j < y_cell_cnt; ++j) {
			int cell_x = i * kFieldSize * 2;
			int cell_y = j * kFieldSize * 2;
			Field* cell = kFieldGenerators[rand() % field_cnt](cell_x, cell_y);

			window.addChild(cell);
		}
	}
}

int main()
{
	srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(), 
                            kWindowHeader, sf::Style::Fullscreen);
	RenderTarget main_rt(window.getSize().x, window.getSize().y);

	Window game_window;
	generateField(game_window, window.getSize());
	WindowManger window_manager(game_window);

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
		
		window_manager.getWindow().draw(main_rt);

		main_rt.display(window);
		window .display();
    }
}