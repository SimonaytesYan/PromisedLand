#include "Menu.hpp"

#include "../Interlayers/CellInterlayer.hpp"
#include "../Events/EventManager.hpp"
#include "../Graphics/Widget/ImageView.hpp"
#include "../GameCycle/GameCycle.hpp"
#include "../Graphics/Widget/BuildingPanel.hpp"
#include "../Graphics/Widget/CellViewGroup.hpp"
#include "../Graphics/Widget/DumyWidget.hpp"
#include "../Graphics/Widget/Toast.hpp"
#include "../Graphics/Widget/MapWidget.hpp"
#include "../Managers/WindowManager.hpp"
#include "../Map/MapGenerating.hpp"
#include "../Map/MapSaveLoad.hpp"
#include "../Utils/SavingScore.hpp"

struct SaveMapArgs
{
	SaveMapArgs(CellInterlayer& cell_int, ResourceManager& res_man, DummyWidget& dummy_widget, EventManager& event_manager, const Point win_size) :
	cell_int      (cell_int),
	res_man       (res_man),
	widget        (dummy_widget),
	event_manager (event_manager),
	win_size      (win_size)
	{ }

	CellInterlayer&  cell_int;
	ResourceManager& res_man;
	DummyWidget&     widget;
	EventManager&    event_manager;
	const Point 	 win_size;
};

void SaveMap(SaveMapArgs args)
{
	MapSaverLoader::saveMapToFile(args.cell_int, args.res_man, "Scripts/Save.sym");

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

void closePause(PauseArgs args) {
	args.pause_win->kill();
	args.event_manager.removeChild(args.pause_win);

	args.event_manager.resetPriorities();
}

void goToMainFunc(PauseArgs args) {
	args.pause_win->kill();
	args.event_manager.removeChild(args.pause_win);
	args.event_manager.resetPriorities();

	args.window_manager.setCurWindow(CreateMenuWindow({args.window, args.rt, args.event_manager, args.window_manager, args.dummy_widget}));
}

void createPauseMenu(PauseArgs args) {
	const auto  window_size   = args.window.getSize();
	const Point pause_win_pos = {(window_size.x - kPauseWinSizeX) / 2, (window_size.y - kPauseWinSizeY) / 2};

	Window* pause_window = new Window(pause_win_pos, window_size.x, window_size.y, "Assets/UI/PauseBack.png");

	const Point button_size(kBtnSizeX, kBtnSizeY);
	Point position(args.window.getSize().x / 2 - button_size.x, kUpperBtnPosY * 3 / 2);

	BasicFunctor* resume_func = new Functor<PauseArgs>(closePause, {args.window, args.rt, args.res_manager, args.event_manager, args.window_manager, args.dummy_widget, args.cell_interlayer, pause_window});
	pause_window->addChild(new Button(position, button_size.x, button_size.y, 
									resume_func, "Assets/UI/ResumeBtn.png"));
	
	BasicFunctor* save_func = new Functor<SaveMapArgs>(SaveMap, {args.cell_interlayer, args.res_manager, args.dummy_widget, args.event_manager, {args.window.getSize().x, args.window.getSize().y}});
	pause_window->addChild(new Button({position.x, position.y + kBtnSizeY + kBtnIndent}, button_size.x, button_size.y, 
									  save_func, "Assets/UI/SaveBtn.png"));

	BasicFunctor* to_main_func = new Functor<PauseArgs>(goToMainFunc, {args.window, args.rt, args.res_manager, args.event_manager, args.window_manager, args.dummy_widget, args.cell_interlayer, pause_window});
	pause_window->addChild(new Button({position.x + kBtnSizeX + kBtnIndent, position.y}, button_size.x, button_size.y, 
									to_main_func, "Assets/UI/MainBtn.png"));

	BasicFunctor* exit_game_func = new Functor<WindowManager&>(exitGame, args.window_manager);
	pause_window->addChild(new Button({position.x + kBtnSizeX + kBtnIndent, position.y + kBtnSizeY + kBtnIndent}, button_size.x, button_size.y, 
									exit_game_func, "Assets/UI/ExitBtn.png"));

	pause_window->setPriority(1);
	args.dummy_widget .addChild(pause_window);
	args.event_manager.addChild(pause_window);
	args.event_manager.privatizeAll(1);
}

void createTopScoreWindow(MenuButtonArgs args)
{
	const auto window_size = args.window.getSize();
	Window* top_score_window = new Window({0, 0}, window_size.x, window_size.y, "Assets/UI/TopScoreBack.png");

	Vector<int> top_score = getTopScore();
	const size_t records_number = (top_score.Size() > 10) ? 10 : top_score.Size();
	Point text_pos{300, 250}; 
	for (size_t i = 0; i < records_number; i++, text_pos.y += 135)
	{
		if (i == 5)
		{
			text_pos.x += 850;
			text_pos.y = 250;
		}

		char content[255] = {};
		
		sprintf(content, "%zu", i + 1);
		top_score_window->addChild(new TextView(text_pos, content, 120));
		sprintf(content, "%d", top_score[i]);
		TextView* score = new TextView({text_pos.x + 250, text_pos.y }, content, 120);
		score->setTextColor({25 * i, 255, 25 * i});
		top_score_window->addChild(score);
	}


	args.window_manager.setCurWindow(top_score_window, nullptr);
}

void CreateGameWindowAndRunGameCycle(MenuButtonArgs args)
{
	const auto   window_size    = args.window.getSize();
	const size_t visible_part_x = (window_size.x - kControlPanelW);
	const size_t visible_part_y = (window_size.y - kControlPanelH);

	Window* game_window = new Window({0, 0}, visible_part_x, visible_part_y, "Assets/Background.png");

	const size_t map_pos_x = window_size.x - kMapScale * kFieldSizeX;
	const size_t map_pos_y = window_size.y - kMapScale * kFieldSizeY;
	MapWidget* map_widget  = new MapWidget({map_pos_x, map_pos_y}, 
							   				kMapScale * kFieldSizeX, 
											kMapScale * kFieldSizeY, 
							   				kMapScale,
											visible_part_x,
											visible_part_y);
	game_window->addChild(map_widget);

	ResourceBar* res_bar = new ResourceBar(args.window.getSize().x, 
										   args.window.getSize().y - kControlPanelH / 2, 
										   kStartResources);
	game_window->addChild(res_bar);

	const int map_area_size_x = std::max(visible_part_x - map_pos_x, 0ul);
	const int map_area_size_y = std::max(visible_part_y - map_pos_y, 0ul);

	CellViewGroup* cell_view_group = new CellViewGroup({0, 0}, 
													   visible_part_x, 
													   visible_part_y, 
													   {map_pos_x, map_pos_y}, 
													   map_area_size_x, 
													   map_area_size_y);
	game_window->addChild(cell_view_group);

	// Interlayer + Manager initialisation
	ResourceBarInterlayer*   res_bar_inter        = new ResourceBarInterlayer(*res_bar);
	ResourceManager*         res_manager          = new ResourceManager(*res_bar_inter);
	CellManager*             cell_manager         = new CellManager(res_manager);
	CellInterlayer*          cell_interlayer      = new CellInterlayer(*cell_manager, *map_widget);
	BuildingPanelInterlayer* build_pan_interlayer = new BuildingPanelInterlayer(*cell_manager);

	res_manager->setCellInterlayer(cell_interlayer);
	map_widget ->setCellInterlayer(cell_interlayer);

	BuildingPanel* build_panel = new BuildingPanel(Point(args.window.getSize().x - kControlPanelW / 2, kControlPanelYStart), 
												   *build_pan_interlayer);
	game_window->addChild(build_panel);

	BasicFunctor* pause_func = new Functor<PauseArgs>(createPauseMenu, {args.window, args.rt, *res_manager, args.event_man, args.window_manager, args.dummy_widget, *cell_interlayer});
	Button* pause_button = new Button({args.window.getSize().x - 112, 12}, 100, 100, 
									  pause_func, "Assets/UI/PauseBtn.png");
	game_window->addChild(pause_button);

	cell_interlayer->setCellViewGroup(cell_view_group);

	cell_manager->setCellInterlayer(cell_interlayer);
	cell_manager->setCellType      (0);

	cell_view_group->setCellInterlayer(cell_interlayer);


	if (args.map_filepath == nullptr)
		generateField(*cell_interlayer);
	else
		MapSaverLoader::loadMapFromFile(*cell_interlayer, *res_manager, args.map_filepath);
		

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
	Point position(args.window.getSize().x / 2 - button_size.x / 2 - kBtnIndent, 
				   kBtnSizeX * 0.85);

	const MenuButtonArgs func_arg = {args.window, args.rt, args.event_manager, 
									 args.window_manager, menu_window, 
									 args.dummy_widget};

	BasicFunctor* run_game_func = new Functor<MenuButtonArgs>(CreateGameWindowAndRunGameCycle, func_arg);
	menu_window->addChild(new Button(position, button_size.x, button_size.y, 
									run_game_func, "Assets/UI/PlayButton.png"));
	
	position.y += button_size.y * 1.2;
	BasicFunctor* load_game_func = new Functor<MenuButtonArgs>(selectLoadingFile, func_arg);
	menu_window->addChild(new Button(position, button_size.x, button_size.y, 
									load_game_func, "Assets/UI/LoadButton.png"));
	
	position.y += button_size.y * 1.2;
	BasicFunctor* load_top_score_window = new Functor<MenuButtonArgs>(createTopScoreWindow, func_arg);
	menu_window->addChild(new Button(position, button_size.x, button_size.y, 
									 load_top_score_window, "Assets/UI/TopScoreBtn.png"));

	return menu_window;
}
