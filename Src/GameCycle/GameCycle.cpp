#include <chrono>

#include "../Events/EventManager.hpp"
#include "GameCycle.hpp"
#include "../Managers/ResourceManager.hpp"
#include "../Constants.hpp"
#include "../Map/MapSaveLoad.hpp"
#include "../Graphics/Widget/AnimatableWidget.hpp"

ResourceManager* ResourceManager::current_manager = nullptr;

void runGameCycle(sf::RenderWindow& window, RenderTarget& rt, Window& game_window, EventManager& event_manager) 
{
	event_manager.addChild(&game_window);

	Vector<const char*> animation;
	animation.PushBack("Assets/UI/Loading/0.png");
	animation.PushBack("Assets/UI/Loading/1.png");
	animation.PushBack("Assets/UI/Loading/2.png");
	animation.PushBack("Assets/UI/Loading/3.png");
	animation.PushBack("Assets/UI/Loading/4.png");
	animation.PushBack("Assets/UI/Loading/5.png");
	animation.PushBack("Assets/UI/Loading/6.png");
	animation.PushBack("Assets/UI/Loading/7.png");

	game_window.addChild(new AnimatedWidget({100, 100}, animation));

    auto timer_start = std::chrono::system_clock::now(); 

	int delta_x = 0, delta_y = 0;
	bool is_map_moving = false, is_clicked = false;
	Point last_pos;

    while (window.isOpen())
	{
		if (ResourceManager::hasLost())
		{
			printf("You have lost!\n");
			event_manager.removeChild(&game_window);
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
			event_manager.push(new Event(EventType::TICK));

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
					break;
				}

				case sf::Event::MouseButtonPressed:
				{
					const auto mouse_position = sf::Mouse::getPosition();

					is_clicked = true;
					last_pos   = {mouse_position.x, mouse_position.y};

					break;
				}

				case sf::Event::MouseButtonReleased:
				{
					if (!is_map_moving) {
						// click on cell
						event_manager.push(new MouseClickEvent({event.mouseButton.x, event.mouseButton.y}));

						// for cell hover
						const auto mouse_position = sf::Mouse::getPosition();
						event_manager.push(new MouseMoveEvent({mouse_position.x, mouse_position.y}));
					}

					is_map_moving = false;
					is_clicked    = false;

					break;
				}

				case sf::Event::MouseMoved:
				{
					if (is_clicked) {
						is_map_moving = true;
						event_manager.push(new MapMovedEvent(last_pos.x - event.mouseMove.x, last_pos.y - event.mouseMove.y));
						last_pos = {event.mouseMove.x, event.mouseMove.y};
					}

					event_manager.push(new MouseMoveEvent({event.mouseMove.x, event.mouseMove.y}));
					
					break;
				}

				case sf::Event::KeyReleased:
				{
					if (event.key.code == sf::Keyboard::W) 
						delta_y = 0;
					else if (event.key.code == sf::Keyboard::A) 
						delta_x = 0;
					else if (event.key.code == sf::Keyboard::S) 
						delta_y = 0;
					else if (event.key.code == sf::Keyboard::D) 
						delta_x = 0;
					else break;

					is_map_moving = false;

					break;
				}

				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::W) 
						delta_y = -1 * move_speed;
					else if (event.key.code == sf::Keyboard::A) 
						delta_x = -1 * move_speed;
					else if (event.key.code == sf::Keyboard::S) 
						delta_y = move_speed;
					else if (event.key.code == sf::Keyboard::D) 
						delta_x = move_speed;
					else break;

					is_map_moving = true;
					event_manager.push(new MapMovedEvent(delta_x, delta_y));

					// for cell hover
					const auto mouse_position = sf::Mouse::getPosition();
					event_manager.push(new MouseMoveEvent({mouse_position.x, mouse_position.y}));

					break;
				}
			}
		}
    }

	event_manager.removeChild(&game_window);
}