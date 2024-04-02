#include <SFML/Graphics.hpp>

#include "RenderTarget.h"

const char* kWindowHeader = "Promised Lands";

int main()
{
    sf::RenderWindow window(sf::VideoMode(), 
                            kWindowHeader, sf::Style::Fullscreen);
	RenderTarget rt(0, 0);
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