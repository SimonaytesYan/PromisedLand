#include <chrono>

#include "../Events/EventManager.hpp"
#include "GameCycle.hpp"
#include "../Managers/ResourceManager.hpp"
#include "../Managers/WindowManager.hpp"
#include "../Graphics/Widget/DumyWidget.hpp"
#include "../Constants.hpp"
#include "../Map/MapSaveLoad.hpp"
#include "../Menu/Menu.hpp"
#include "../Graphics/Widget/Button.hpp"

ResourceManager* ResourceManager::current_manager = nullptr; 

void goToMainFunc(CreateMenuArgs args) {
	args.window_manager.setCurWindow(CreateMenuWindow(args));
}

void exitGame(WindowManager& win_manager) {
	win_manager.setCurWindow(nullptr);
}

Window* createOnLoseWindow(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_manager, WindowManager& window_manager, DummyWidget& dummy_widget) {
	const auto win_size = window.getSize();

	Window* lose_window = new Window({0, 0}, win_size.x, win_size.y, "Assets/UI/LoseWinBack.png");

	const Point button_size(400, 200);
	Point position(window.getSize().x / 2 - button_size.x / 2 - 20, 400);

	BasicFunctor* main_btn_func = new Functor<CreateMenuArgs>(goToMainFunc, {window, rt, event_manager, window_manager, dummy_widget});
	lose_window->addChild(new Button(position, button_size.x, button_size.y, 
									main_btn_func, "Assets/UI/MainBtn.png"));
	
	position.y += button_size.y * 1.5;
	BasicFunctor* load_game_func = new Functor<WindowManager&>(exitGame, window_manager);
	lose_window->addChild(new Button(position, button_size.x, button_size.y, 
									load_game_func, "Assets/UI/ExitBtn.png"));
	
	return lose_window;
}

void runGameCycle(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_manager, WindowManager& window_manager, DummyWidget& dummy_widget) 
{
    auto timer_start = std::chrono::system_clock::now(); 

	int delta_x = 0, delta_y = 0;
	bool is_map_moving = false, is_clicked = false;
	Point last_pos;

    while (window.isOpen())
	{
		if (!window_manager.getCurWindow()) return;
		
		if (ResourceManager::hasLost())
		{
			fprintf(stderr, "You have lost!\n");
			window_manager.setCurWindow(createOnLoseWindow(window, rt, event_manager, window_manager, dummy_widget));
		}

		rt.clear();
		window.clear();

		dummy_widget.draw(rt);
		
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
}