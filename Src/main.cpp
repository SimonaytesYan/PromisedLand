#include <chrono>
#include <functional>

#include <SFML/Graphics.hpp>

#include "constants.hpp"

void runGameCycle(const sf::RenderWindow& window) {
    auto timer_start = std::chrono::system_clock::now(); 
    while (window.isOpen())
	{
		// TODO: switch to EventManager
		auto timer_end = std::chrono::system_clock::now();
        auto passed   = std::chrono::duration_cast<std::chrono::milliseconds>(timer_end - timer_start);
		if (passed.count() >= kMSInClock)
		{
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

int main()
{
	srand(time(nullptr));

    sf::RenderWindow window(sf::VideoMode(), 
                            kWindowHeader, sf::Style::Fullscreen);
	RenderTarget main_rt(window.getSize().x, window.getSize().y);


	runGameCycle(window);
}