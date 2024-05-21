#pragma once

#include "../Events/EventManager.hpp"
#include "../Graphics/Widget/DumyWidget.hpp"
#include "../Graphics/Widget/Window.hpp"
#include "../Utils/Functor.hpp"

class WindowManager
{
public:

    WindowManager(EventManager& event_manager, DummyWidget& dummy_widget)
      : cur_window    (nullptr),
        event_manager (event_manager),
        dummy_widget  (dummy_widget),
        on_win_changed(nullptr)
    {}

    explicit WindowManager(Window* window, EventManager& event_manager, DummyWidget& dummy_widget)
      : cur_window    (window),
        event_manager (event_manager),
        dummy_widget  (dummy_widget),
        on_win_changed(nullptr)
    {
        setCurWindow(cur_window);
    }

    void setCurWindow(Window* _cur_window, BasicFunctor* _on_win_changed = nullptr)
    {
        if (cur_window)
        {
            event_manager.removeChild(cur_window);
            cur_window->kill();

            if (on_win_changed) {
                (*on_win_changed)();
            }
        }

        cur_window = _cur_window;
        dummy_widget .addChild(cur_window);
	    event_manager.addChild(cur_window);

        on_win_changed = _on_win_changed;
    }

    Window* getCurWindow() const
    {
        return cur_window;
    }

    ~WindowManager()
    {
        if (cur_window)
        {
            event_manager.removeChild(cur_window);
			dummy_widget .removeChild(cur_window);
            delete cur_window;
        }
    }

private:
    // owns it
    Window*       cur_window;
    BasicFunctor* on_win_changed;
    EventManager& event_manager;
    DummyWidget&  dummy_widget;
};