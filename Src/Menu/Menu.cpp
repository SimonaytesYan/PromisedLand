#include "Menu.hpp"

#include "../Interlayers/CellInterlayer.hpp"
#include "../Events/EventManager.hpp"
#include "../Graphics/Widget/ImageView.hpp"
#include "../GameCycle/GameCycle.hpp"
#include "../Graphics/Widget/BuildingPanel.hpp"
#include "../Graphics/Widget/CellViewGroup.hpp"
#include "../Graphics/Widget/DumyWidget.hpp"
#include "../Graphics/Widget/Toast.hpp"
#include "../Managers/WindowManager.hpp"
#include "../Map/MapGenerating.hpp"
#include "../Map/MapSaveLoad.hpp"

void SaveMap(SaveMapArgs args)
{
	MapSaver::saveMapToFile(args.cell_int, "Scripts/Save.sym");

	// deletes itself after duration finished
	new Toast(args.win_size.x, args.win_size.y, kSaveSuccessful, args.event_manager, args.widget);
}

void freeGameManagers(GameSettings args) {
	delete args.build_pan_interlayer;
	delete args.cell_interlayer;
	delete args.cell_manager;
	delete args.res_bar_inter;
	delete args.res_manager;
}

void CreateGameWindowAndRunGameCycle(MenuButtonArgs args)
{
	const auto   window_size    = args.window.getSize();
	const size_t visible_part_x = (window_size.x - kControlPanelW);
	const size_t visible_part_y = (window_size.y - kControlPanelH);

	Window* game_window = new Window({0, 0}, visible_part_x, visible_part_y, "Assets/Background.png");

	ResourceBar* res_bar = new ResourceBar(args.window.getSize().x, 
										   args.window.getSize().y - kControlPanelH / 2, 
										   kStartResources);
	game_window->addChild(res_bar);

	CellViewGroup* cell_view_group = new CellViewGroup({0, 0}, visible_part_x, visible_part_y);
	game_window->addChild(cell_view_group);

	// Interlayer + Manager initialisation
	ResourceBarInterlayer*   res_bar_inter        = new ResourceBarInterlayer(*res_bar);
	ResourceManager*         res_manager          = new ResourceManager(*res_bar_inter);
	CellManager*             cell_manager         = new CellManager(res_manager);
	CellInterlayer*          cell_interlayer      = new CellInterlayer(*cell_manager);
	BuildingPanelInterlayer* build_pan_interlayer = new BuildingPanelInterlayer(*cell_manager);

	res_manager->setCellInterlayer(cell_interlayer);

	BuildingPanel* build_panel = new BuildingPanel(Point(args.window.getSize().x - kControlPanelW / 2, kControlPanelYStart), 
												   *build_pan_interlayer);
	game_window->addChild(build_panel);

	BasicFunctor* save_func = new Functor<SaveMapArgs>(SaveMap, {*cell_interlayer, args.dummy_widget, args.event_man, {args.window.getSize().x, args.window.getSize().y}});
	Button* save_button = new Button({args.window.getSize().x - 112, 12}, 100, 100, 
									  save_func, "Assets/UI/SaveIcon.png");
	game_window->addChild(save_button);

	cell_interlayer->setCellViewGroup(cell_view_group);

	cell_manager->setCellInterlayer(cell_interlayer);
	cell_manager->setCellType      (0);

	cell_view_group->setCellInterlayer(cell_interlayer);

	if (args.map_filepath == nullptr)
		generateField(*cell_interlayer);
	else
		loadMapFromFile(*cell_interlayer, args.map_filepath);

	args.window_manager.setCurWindow(game_window, new Functor<GameSettings>(freeGameManagers, {res_bar_inter, res_manager, cell_manager, cell_interlayer, build_pan_interlayer}));
}

void selectLoadingFile(MenuButtonArgs args)
{
	args.map_filepath = "Scripts/Save.sym";
	CreateGameWindowAndRunGameCycle(args);
}

Window* CreateMenuWindow(CreateMenuArgs args)
{
	const auto window_size = args.window.getSize();

	Window* menu_window = new Window({0, 0}, window_size.x, window_size.y, "Assets/UI/MenuBackground.png");

	const Point button_size(kBtnSizeX, kBtnSizeY);
	Point position(args.window.getSize().x / 2 - button_size.x / 2 - kBtnIndent, kBtnSizeX);

	BasicFunctor* run_game_func = new Functor<MenuButtonArgs>(CreateGameWindowAndRunGameCycle, {args.window, args.rt, args.event_manager, args.window_manager, menu_window, args.dummy_widget});
	menu_window->addChild(new Button(position, button_size.x, button_size.y, 
									run_game_func, "Assets/UI/PlayButton.png"));
	
	position.y += button_size.y * 1.5;
	BasicFunctor* load_game_func = new Functor<MenuButtonArgs>(selectLoadingFile, {args.window, args.rt, args.event_manager, args.window_manager, menu_window, args.dummy_widget});
	menu_window->addChild(new Button(position, button_size.x, button_size.y, 
									load_game_func, "Assets/UI/LoadButton.png"));
	
	return menu_window;
}
