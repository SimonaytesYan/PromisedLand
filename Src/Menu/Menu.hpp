#pragma once

#include "../Events/EventManager.hpp"
#include "../Graphics/Widget/Window.hpp"
#include "../Graphics/Widget/DumyWidget.hpp"
#include "../Utils/RenderTarget.hpp"
#include "../Interlayers/CellInterlayer.hpp"

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

struct SaveMapArgs
{
	SaveMapArgs(CellInterlayer& cell_int, DummyWidget& widget, EventManager& event_manager, const Point win_size)
	  : cell_int      (cell_int),
	  	widget        (widget),
		event_manager (event_manager),
		win_size      (win_size)
	{}  

	CellInterlayer& cell_int;
	DummyWidget&    widget;
	EventManager&   event_manager;
	const Point 	win_size;
};

static const char* kLoadImg  = "Assets/load.png";
static const int   kLoadImgW = 456;
static const int   kLoadImgH = 256;

static const char* kSaveSuccessful = "Saved successfully!";
static const int   kBorderIndent   = 5;

Window* CreateMenuWindow(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_manager, DummyWidget& dummy_widget);