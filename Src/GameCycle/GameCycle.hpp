#pragma once

#include "../Utils/RenderTarget.hpp"
#include "../Graphics/Widget/Window.hpp"
#include "../Graphics/Widget/DumyWidget.hpp"

void runGameCycle(sf::RenderWindow& window, RenderTarget& rt, Window& game_window, EventManager& event_manager, DummyWidget& dummy_widget);
