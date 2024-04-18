#include "CellViewGroup.hpp"

void CellViewGroup::push(const EventPtr event)
{        
    switch (event->event_type)
    {
        case EventType::TICK:
            assert(cell_interlayer);
            cell_interlayer->pushToLogic(event);
            break;
        case EventType::BUILD_CELL_EVENT:
        {  
            const CreateCellViewEvent* build_event = static_cast<const CreateCellViewEvent*>(event.get());
            addCell(build_event->cell_view);
            break;
        }  
        case EventType::DESTROY_CELL_EVENT:
        {  
            const DestroyCellEvent* delete_event = static_cast<const DestroyCellEvent*>(event.get());
            delete_event->cell_view->kill();
            break;
        }   
        default:
            break;
    }

    for (auto val : cell_views)
        val->push(event);
}

void CellViewGroup::draw(RenderTarget& rt)
{
    deleteDeadCells();

    const size_t cell_view_size = cell_views.size();
    for (size_t index = 0; index < cell_view_size; index++)
        cell_views[index]->draw(rt);
}

void CellViewGroup::deleteDeadCells()
{
    bool recalc_indexes = false;
    for (int index = cell_views.size() - 1; index >= 0; index--)
    {
        if (!((cell_views[index])->isAlive()))
        {
            delete cell_views[index];
            cell_views.erase(cell_views.begin() + index);
            recalc_indexes = true;
        }    
    }

    if (recalc_indexes)
    {
        const size_t cell_views_size = cell_views.size();
        for (size_t index = 0; index < cell_views_size; index++)
            cell_views[index]->setIndexInCellGroup(index);
    }
}