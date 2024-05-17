#include "Menu.hpp"

#include "../Interlayers/CellInterlayer.hpp"
#include "../Events/EventManager.hpp"
#include "../GameCycle/GameCycle.hpp"
#include "../Graphics/Widget/BuildingPanel.hpp"
#include "../Graphics/Widget/CellViewGroup.hpp"
#include "../Map/MapGenerating.hpp"
#include "../Map/MapSaveLoad.hpp"

struct SaveMapArgs
{
	SaveMapArgs(CellInterlayer& cell_int, ResourceManager& res_man) :
	cell_int (cell_int),
	res_man  (res_man)
	{ }

	CellInterlayer& cell_int;
	ResourceManager& res_man;
};

void SaveMap(SaveMapArgs args)
{
	MapSaverLoader::saveMapToFile(args.cell_int, args.res_man, "Scripts/Save.sym");
}

void createWaitWindow()
{
	
}

void CreateGameWindowAndRunGameCycle(MenuButtonArgs args)
{
	args.event_man.removeChild(args.game_window);

	const auto   window_size    = args.window.getSize();
	const size_t visible_part_x = (window_size.x - kControlPanelW);
	const size_t visible_part_y = (window_size.y - kControlPanelH);

	Window game_window({0, 0}, visible_part_x, visible_part_y, "Assets/Background.png");

	ResourceBar* res_bar = new ResourceBar(args.window.getSize().x, 
										   args.window.getSize().y - kControlPanelH / 2, 
										   kStartResources);
	game_window.addChild(res_bar);

	CellViewGroup* cell_view_group = new CellViewGroup({0, 0}, visible_part_x, visible_part_y);
	game_window.addChild(cell_view_group);

	// Interlayer + Manager initialisation
	ResourceBarInterlayer   res_bar_inter(*res_bar);
	ResourceManager         res_manager(res_bar_inter);
	CellManager             cell_manager(&res_manager);
	CellInterlayer          cell_interlayer(cell_manager);
	BuildingPanelInterlayer build_pan_interlayer(cell_manager);

	res_manager.setCellInterlayer(&cell_interlayer);

	BuildingPanel* build_panel = new BuildingPanel(Point(args.window.getSize().x - kControlPanelW / 2, kControlPanelYStart), 
												   build_pan_interlayer);
	game_window.addChild(build_panel);

	BasicFunctor* save_func = new Functor<SaveMapArgs>(SaveMap, SaveMapArgs(cell_interlayer, res_manager));
	Button* save_button = new Button({args.window.getSize().x - 112, 12}, 100, 100, 
									  save_func, "Assets/UI/SaveIcon.png");
	game_window.addChild(save_button);

	cell_interlayer.setCellViewGroup(cell_view_group);

	cell_manager.setCellInterlayer(&cell_interlayer);
	cell_manager.setCellType      (0);

	cell_view_group->setCellInterlayer(&cell_interlayer);

	if (args.map_filepath == nullptr)
		generateField(cell_interlayer);
	else
		MapSaverLoader::loadMapFromFile(cell_interlayer, res_manager, args.map_filepath);

	runGameCycle(args.window, args.rt, game_window, args.event_man);
	args.event_man.addChild(args.game_window);
}

void selectLoadingFile(MenuButtonArgs args)
{
	args.map_filepath = "Scripts/Save.sym";
	CreateGameWindowAndRunGameCycle(args);
}

Window* CreateMenuWindow(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_manager)
{
	const auto window_size = window.getSize();

	RenderTarget menu_rt(Point(window_size.x, window_size.y));
	Window* menu_window = new Window({0, 0}, window_size.x, window_size.y, "Assets/UI/MenuBackground.png");

	const Point button_size(400, 200);
	Point position(window.getSize().x / 2 - button_size.x / 2 - 20, 400);

	BasicFunctor* run_game_func = new Functor<MenuButtonArgs>(CreateGameWindowAndRunGameCycle, {window, rt, event_manager, menu_window});
	menu_window->addChild(new Button(position, button_size.x, button_size.y, 
									run_game_func, "Assets/UI/PlayButton.png"));
	
	position.y += button_size.y * 1.5;
	BasicFunctor* load_game_func = new Functor<MenuButtonArgs>(selectLoadingFile, {window, rt, event_manager, menu_window});
	menu_window->addChild(new Button(position, button_size.x, button_size.y, 
									load_game_func, "Assets/UI/LoadButton.png"));
	
	return menu_window;
}
