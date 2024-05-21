#pragma once

#include "../Events/EventManager.hpp"
#include "../Graphics/Widget/Window.hpp"
#include "../Graphics/Widget/DumyWidget.hpp"
#include "../Utils/RenderTarget.hpp"
#include "../Interlayers/CellInterlayer.hpp"
#include "../Managers/WindowManager.hpp"

struct MenuButtonArgs
{
	MenuButtonArgs(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_man, WindowManager& window_manager, Window* game_window, DummyWidget& dummy_widget, const char* map_filepath = nullptr) : 
	window		   (window),
	rt			   (rt),
	event_man      (event_man),
	game_window    (game_window),
	dummy_widget   (dummy_widget),
	window_manager (window_manager),
	map_filepath   (map_filepath)
	{ }

	sf::RenderWindow& window;
	RenderTarget& 	  rt;
	EventManager&     event_man;
	Window*           game_window;
	DummyWidget& 	  dummy_widget;
	WindowManager&    window_manager;
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

class ResourceBarInterlayer;
class ResourceManager;
class BuildingPanelInterlayer;
struct GameSettings {
	ResourceBarInterlayer*   res_bar_inter;
	ResourceManager*         res_manager;
	CellManager*             cell_manager;
	CellInterlayer*          cell_interlayer;
	BuildingPanelInterlayer* build_pan_interlayer;
};

struct CreateMenuArgs {
	sf::RenderWindow& window;
	RenderTarget&     rt;
	EventManager&     event_manager;
	WindowManager&    window_manager;
	DummyWidget&      dummy_widget;
};

struct PauseArgs {
	sf::RenderWindow& window;
	RenderTarget&     rt;
	EventManager&     event_manager;
	WindowManager&    window_manager;
	DummyWidget&      dummy_widget;
	CellInterlayer&   cell_interlayer;

	Window* pause_win = nullptr;
};

static const char* kLoadImg  = "Assets/load.png";
static const int   kLoadImgW = 456;
static const int   kLoadImgH = 256;

static const char* kSaveSuccessful = "Saved successfully!";
static const int   kBorderIndent   = 5;

static const int kBtnSizeX  = 400;
static const int kBtnSizeY  = 200;
static const int kBtnIndent = 20;

static const int kPauseWinSizeX = 1000;
static const int kPauseWinSizeY = 800;
static const int kUpperBtnPosY  = 250;

Window* CreateMenuWindow(CreateMenuArgs args);