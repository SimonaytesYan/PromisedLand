#include <chrono>
#include <functional>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Utils/RenderTarget.hpp"

void runGameCycle(sf::RenderWindow& window, RenderTarget& rt) 
{
	Texture test_img("Assets/field.png");

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

				}
			}
		}

		rt.drawRect   ({20, 20}, {100, 100}, sf::Color::Red, 5, sf::Color::Blue);
		rt.drawCircle ({40, 40}, 20, sf::Color::Cyan, 2, sf::Color::Green);
		rt.setPixel   ({25, 25}, sf::Color::Magenta);
		rt.drawLine   ({10, 10}, {400, 400}, sf::Color::Blue);
		rt.drawText   ({100, 100}, "TEST", 20, sf::Color::Yellow);
		rt.drawTexture({300, 300}, test_img);

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