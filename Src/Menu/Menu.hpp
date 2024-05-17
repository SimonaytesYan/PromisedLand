#pragma once

#include "../Events/EventManager.hpp"
#include "../Graphics/Widget/Window.hpp"
#include "../Graphics/Widget/DumyWidget.hpp"
#include "../Utils/RenderTarget.hpp"

struct MenuButtonArgs
{
	MenuButtonArgs(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_man, Window* game_window, DummyWidget& dummy_widget, const char* map_filepath = nullptr) : 
	window		 (window),
	rt			 (rt),
	event_man    (event_man),
	game_window  (game_window),
	dummy_widget (dummy_widget),
	map_filepath (map_filepath)
	{ }

	sf::RenderWindow& window;
	RenderTarget& 	  rt;
	EventManager&     event_man;
	Window*           game_window;
	DummyWidget& 	  dummy_widget;
	const char*		  map_filepath;
};

static const char* load_img   = "Assets/load.png";
static const int   load_img_w = 456;
static const int   load_img_h = 256;

Window* CreateMenuWindow(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_manager, DummyWidget& dummy_widget);