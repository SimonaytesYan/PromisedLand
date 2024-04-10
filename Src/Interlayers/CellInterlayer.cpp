#include "CellInterlayer.hpp"
#include "../Graphics/Widget/Window.hpp"

void CellInterlayer::pushToView(const Event* event)
{
    const size_t cell_views_size = cell_views.Size();
    for (size_t i = 0; i < cell_views_size; i++)
        cell_views[i]->push(event);
    window->push(event);
}