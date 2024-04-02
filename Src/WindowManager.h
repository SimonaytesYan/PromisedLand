#include "Window.h"


class WindowManger
{
public:
    WindowManger(Window& window) :
    window (window)
    { }

    Window& getWindow() const
    { return window; }

    void setWindow(Window& new_window)
    { window = new_window; }

private:
    Window& window;
};