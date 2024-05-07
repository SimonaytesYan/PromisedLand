#pragma once

#include "../Graphics/Widget/Window.hpp"
#include "../Utils/RenderTarget.hpp"

struct MenuButtonArgs
{
	MenuButtonArgs(sf::RenderWindow& window, RenderTarget& rt, const char* map_filepath = nullptr) : 
	window		 (window),
	rt			 (rt),
	map_filepath (map_filepath)
	{ }

	sf::RenderWindow& window;
	RenderTarget& 	  rt;
	const char*		  map_filepath;
};

Window CreateMenuWindow(sf::RenderWindow& window, RenderTarget& rt);