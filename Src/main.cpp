#include <chrono>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Graphics/Widget/BuildingPanel.hpp"
#include "Interlayers/CellInterlayer.hpp"
#include "Graphics/Widget/CellViewGroup.hpp"
#include "Graphics/CellView/CellViewCreator.hpp"
#include "Constants.hpp"
#include "Utils/RenderTarget.hpp"
#include "Graphics/Widget/Window.hpp"

void generateField(CellInterlayer& cell_int, const sf::Vector2u window_size)
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

			cell_int.createCell(FieldType::Grass, {cell_x, cell_y});
		}
	}
}

void runGameCycle(sf::RenderWindow& window, RenderTarget& rt) 
{
	Window game_window({0, 0});

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
	cell_manager.setCellType      (FieldType::Grass);

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
			// printf("You have lost!\n");
			// window.close();
		}

		rt.clear();
		window.clear();

		game_window.draw(rt);

		rt.display(window);
		window.display();
    }
}

int main()
{
	srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);
	RenderTarget main_rt(window.getSize());

	runGameCycle(window, main_rt);
}