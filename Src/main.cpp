#include <SFML/Graphics.hpp>
#include "Window.h"
#include "WindowManager.h"

const char* kWindowHeader = "Promised Lands";

int main()
{
    sf::RenderWindow window(sf::VideoMode(), 
                            kWindowHeader, sf::Style::Fullscreen);

	
	Window game_window;
	WindowManger window_manager();
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
    }
}