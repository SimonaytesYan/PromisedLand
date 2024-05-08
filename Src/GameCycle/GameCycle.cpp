#include <chrono>

#include "GameCycle.hpp"
#include "../Managers/ResourceManager.hpp"
#include "../Constants.hpp"
#include "../Map/MapSaveLoad.hpp"

ResourceManager* ResourceManager::current_manager = nullptr;

void runGameCycle(sf::RenderWindow& window, RenderTarget& rt, Window& game_window) 
{
    auto timer_start = std::chrono::system_clock::now(); 
    while (window.isOpen())
	{
		if (ResourceManager::hasLost())
		{
			printf("You have lost!\n");
			// window.close();
            return;
		}

		rt.clear();
		window.clear();

		game_window.draw(rt);
		
		rt.display(window);
		window.display();

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
    }
}