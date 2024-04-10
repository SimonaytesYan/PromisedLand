#include <chrono>
#include <functional>

#include <SFML/Graphics.hpp>

#include "GameLogic/Views/Tiles/CellView.hpp"
#include "Constants.hpp"
#include "Utils/RenderTarget.hpp"
#include "GameLogic/Managers/ResourceManager.hpp"
#include "GameLogic/Views/TextView/ResourceBar.hpp"
#include "GameLogic/Views/Window.hpp"

// void runGameCycle(sf::RenderWindow& window, RenderTarget& rt) 
// {
// 	// just testing
// 	ResourceManager resource_manager;
// 	Window          game_window({0, 0}, resource_manager);

// 	CellView* test_cell1 = new CellView({0, 0}, FieldType::House, resource_manager);
// 	CellView* test_cell2 = new CellView({0, 0}, FieldType::House, resource_manager);
// 	CellView* test_cell3 = new CellView({0, 0}, FieldType::House, resource_manager);

// 	game_window.addChild(test_cell1);
// 	game_window.addChild(test_cell2);
// 	game_window.addChild(test_cell3);

// 	game_window.addChild(new ResourceBar(1920, 50, resource_manager));

//     auto timer_start = std::chrono::system_clock::now(); 
//     while (window.isOpen())
// 	{
// 		auto timer_end = std::chrono::system_clock::now();
//         auto passed   = std::chrono::duration_cast<std::chrono::milliseconds>(timer_end - timer_start);
// 		if (passed.count() >= kMSInClock)
// 		{
// 			Event tick_event(EventType::TICK);
// 			game_window.push(&tick_event);

// 			timer_start = timer_end;
// 		}

// 		sf::Event event;
// 		while (window.pollEvent(event))
// 		{
// 			switch (event.type)
// 			{
// 				case sf::Event::Closed:
// 				{
// 					window.close();
// 				}

// 				case sf::Event::MouseButtonPressed:
// 				{

// 				}
// 			}
// 		}
// 		rt.clear();
// 		window.clear();

// 		game_window.draw(rt);

// 		rt.display(window);
// 		window.display();
//     }
// }

int main()
{
	srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(), kWindowHeader, sf::Style::Fullscreen);
	RenderTarget main_rt(window.getSize());

	// runGameCycle(window, main_rt);
}