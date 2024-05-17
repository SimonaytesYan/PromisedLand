#pragma once

#include "../Events/EventManager.hpp"
#include "../Graphics/Widget/Window.hpp"
#include "../Utils/RenderTarget.hpp"

struct MenuButtonArgs
{
	MenuButtonArgs(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_man, Window* game_window, const char* map_filepath = nullptr) : 
	window		 (window),
	rt			 (rt),
	event_man    (event_man),
	game_window  (game_window),
	map_filepath (map_filepath)
	{ }

	sf::RenderWindow& window;
	RenderTarget& 	  rt;
	EventManager&     event_man;
	Window*           game_window;
	const char*		  map_filepath;
};

Window* CreateMenuWindow(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_manager);