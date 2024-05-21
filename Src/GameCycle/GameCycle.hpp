#pragma once

#include "../Utils/RenderTarget.hpp"
#include "../Graphics/Widget/Window.hpp"
#include "../Graphics/Widget/DumyWidget.hpp"
#include "../Managers/WindowManager.hpp"

void runGameCycle(sf::RenderWindow& window, RenderTarget& rt, EventManager& event_manager, WindowManager& window_manager, DummyWidget& dummy_widget);
