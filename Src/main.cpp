#include <chrono>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Graphics/Widget/BuildingPanel.hpp"
#include "Graphics/CellView/CellViewCreator.hpp"
#include "Constants.hpp"
#include "Utils/RenderTarget.hpp"
#include "Graphics/Widget/Window.hpp"

void generateField(Window& window, CellInterlayer& cell_int, const sf::Vector2u window_size)
{
	// leave space for controls below
	const int x_cell_cnt = (window_size.x - kControlPanelW) / kFieldSize;
	const int y_cell_cnt = (window_size.y - kControlPanelH) / kFieldSize;

	for (int i = 0; i <= x_cell_cnt; ++i) 
	{
		for (int j = 0; j <= y_cell_cnt; ++j) 
		{
			const int cell_x    = i * kFieldSize;
			const int cell_y    = j * kFieldSize;
			
			// window.
		}
	}
}

void runGameCycle(sf::RenderWindow& window, RenderTarget& rt) 
{
	Window game_window({0, 0});
	BuildingPanel

    auto timer_start = std::chrono::system_clock::now(); 
    while (window.isOpen())
	{
		auto timer_end = std::chrono::system_clock::now();
        auto passed   = std::chrono::duration_cast<std::chrono::milliseconds>(timer_end - timer_start);
		if (passed.count() >= kMSInClock)
		{
			// Event tick_event(EventType::TICK);
			// game_window.push(&tick_event);

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

				}
			}
		}

		rt.clear();
		window.clear();

		rt.display(window);
		window.display();
    }
}

int main()
{
	srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);
	RenderTarget main_rt(window.getSize());

	ResourceBarInterlayer res_bar_interlayer;
	ResourceManager res_manager;

	runGameCycle(window, main_rt);
}