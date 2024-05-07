#include "Menu.hpp"

#include "../Interlayers/CellInterlayer.hpp"
#include "../GameCycle/GameCycle.hpp"
#include "../Graphics/Widget/BuildingPanel.hpp"
#include "../Graphics/Widget/CellViewGroup.hpp"
#include "../Map/MapGenerating.hpp"
#include "../Map/MapSaveLoad.hpp"

void CreateGameWindowAndRunGameCycle(MenuButtonArgs args)
{
	Window game_window({0, 0}, "Assets/Background.png");

	ResourceBar* res_bar = new ResourceBar(args.window.getSize().x, 
										   args.window.getSize().y - kControlPanelH / 2, 
										   kStartResources);
	game_window.addChild(res_bar);

	CellViewGroup* cell_view_group = new CellViewGroup({0, 0});
	game_window.addChild(cell_view_group);

	// Interlayer + Manager initialisation
	ResourceBarInterlayer   res_bar_inter(*res_bar);
	ResourceManager         res_manager(res_bar_inter);
	CellManager             cell_manager(&res_manager);
	CellInterlayer          cell_interlayer(cell_manager);
	BuildingPanelInterlayer build_pan_interlayer(cell_manager);

	BuildingPanel* build_panel = new BuildingPanel(Point(args.window.getSize().x - kControlPanelW / 2, kControlPanelYStart), 
												   build_pan_interlayer);
	game_window.addChild(build_panel);

	cell_interlayer.setCellViewGroup(cell_view_group);

	cell_manager.setCellInterlayer(&cell_interlayer);
	cell_manager.setCellType      (0);

	cell_view_group->setCellInterlayer(&cell_interlayer);

	if (args.map_filepath == nullptr)
		generateField(cell_interlayer, args.window.getSize());
	else
		createFieldFromFile(cell_interlayer, args.window.getSize(), args.map_filepath);

	runGameCycle(args.window, args.rt, game_window);
}

void selectLoadingFile(MenuButtonArgs args)
{
	args.map_filepath = "Scripts/Test.sym";
	CreateGameWindowAndRunGameCycle(args);
}

Window CreateMenuWindow(sf::RenderWindow& window, RenderTarget& rt)
{
	RenderTarget menu_rt(Point(window.getSize().x, window.getSize().y));
	Window menu_window({0, 0}, "Assets/UI/MenuBackground.png");

	const Point button_size(400, 200);
	Point position(window.getSize().x / 2 - button_size.x / 2 - 20, 400);

	BasicFunctor* run_game_func = new Functor<MenuButtonArgs>(CreateGameWindowAndRunGameCycle, {window, rt});
	menu_window.addChild(new Button(position, button_size.x, button_size.y, 
									run_game_func, "Assets/UI/PlayButton.png"));
	
	position.y += button_size.y * 1.5;
	BasicFunctor* load_game_func = new Functor<MenuButtonArgs>(selectLoadingFile, {window, rt});
	menu_window.addChild(new Button(position, button_size.x, button_size.y, 
									load_game_func, "Assets/UI/LoadButton.png"));
	
	return menu_window;
}
