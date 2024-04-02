#include <SFML/Graphics.hpp>
#include "Window.h"
#include "WindowManager.h"

#include "RenderTarget.h"

const char* kWindowHeader = "Promised Lands";

int main()
{
    sf::RenderWindow window(sf::VideoMode(), 
                            kWindowHeader, sf::Style::Fullscreen);

	
	Window game_window;
	WindowManger window_manager();
	RenderTarget rt(window.getSize().x, window.getSize().y);
	Texture test_img("Assets/test.jpg");

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
		rt.drawRect  (20, 20, 100, 100, sf::Color::Red, 5, sf::Color::Blue);
		rt.drawCircle(40, 40, 20, sf::Color::Cyan, 2, sf::Color::Green);
		rt.setPixel(25, 25, sf::Color::Magenta);
		rt.drawLine(10, 10, 400, 400, sf::Color::Blue);
		rt.drawText(100, 100, "TEST", 20, sf::Color::Yellow);
		rt.drawTexture(300, 300, test_img);

		rt.display(window);
		window.display();
    }
}