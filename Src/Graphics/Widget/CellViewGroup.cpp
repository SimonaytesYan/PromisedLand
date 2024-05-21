#include "CellViewGroup.hpp"

#include "../../Interlayers/CellInterlayer.hpp"
#include "../../CellLoader/CellKeeper.hpp"
#include "../../Events/Events.hpp"
#include "../CellView/CellView.hpp"

CellViewGroup::CellViewGroup(const Point position, 
                             const size_t _map_size_x, 
                             const size_t _map_size_y, 
                             const Point  _inv_area_pos,
                             const size_t _inv_area_size_x,
                             const size_t _inv_area_size_y)
  : Widget (position)
{ 
    const size_t canvas_size_x = kFieldSizeX * kCellSize;
    const size_t canvas_size_y = kFieldSizeY * kCellSize;

    const size_t map_size_x = std::min(_map_size_x, canvas_size_x);
    const size_t map_size_y = std::min(_map_size_y, canvas_size_y);

    draw_canvas = new Canvas(position, 
                             map_size_x, 
                             map_size_y, 
                             canvas_size_x, 
                             canvas_size_y, 
                             _inv_area_pos, 
                             _inv_area_size_x, 
                             _inv_area_size_y);
}

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
            addCell(build_event->cell_type, build_event->pos);
            
            break;
        }  
        case EventType::DESTROY_CELL_VIEW_EVENT:
        {  
            const DestroyCellViewEvent* delete_event = static_cast<const DestroyCellViewEvent*>(event.get());
            delete_event->cell_view->kill();
            
            const size_t index = delete_event->cell_view->getIndex();
            cell_interlayer->pushToLogic(new DestroyCellLogicEvent(index));
            
            break;
        }
        case EventType::REBUILD_EVENT:
        {
            const RebuildEvent* rebuild_event = static_cast<const RebuildEvent*>(event.get());
            
            cell_views[rebuild_event->index]->kill();
            addCell(rebuild_event->cell_type, cell_views[rebuild_event->index]->getPos());
            break;
        }
        case EventType::COEFF_CHANGED:
        {
            const CoeffChangedEvent* coeff_changed_event = static_cast<const CoeffChangedEvent*>(event.get());
            cell_views[coeff_changed_event->index]->setCoeff(coeff_changed_event->cur_workers, coeff_changed_event->max_workers);
            break;
        }
        case EventType::MAP_MOVED:
        {
            const MapMovedEvent* map_moved_event = static_cast<const MapMovedEvent*>(event.get());
            const auto dx = map_moved_event->delta_x;
            const auto dy = map_moved_event->delta_y;

            Point new_pos = draw_canvas->updateHostPosition(dx, dy);
            cell_interlayer->pushToView(new SmallMapMovedEvent(new_pos));

            break;
        }
        case EventType::MOUSE_CLICK:
        {
            const MouseClickEvent* mouse_event = static_cast<const MouseClickEvent*>(event.get());

            if (!draw_canvas->isScreenPointInCanvas(mouse_event->pos)) return;

            EventPtr cell_view_event = new MouseClickEvent(draw_canvas->getRelativePos(mouse_event->pos));
            for (auto val : cell_views)
            {
                if (draw_canvas->isCellVisible(val->getPos(), kCellSize))
                    val->push(cell_view_event);
            }

            return;
        }
        case EventType::MOUSE_MOVE:
        {
            const MouseMoveEvent* mouse_event = static_cast<const MouseMoveEvent*>(event.get());

            if (!draw_canvas->isScreenPointInCanvas(mouse_event->pos)) return;

            EventPtr cell_view_event = new MouseMoveEvent(draw_canvas->getRelativePos(mouse_event->pos));
            for (auto val : cell_views)
            {
                if (draw_canvas->isCellVisible(val->getPos(), kCellSize))
                    val->push(cell_view_event);
            }

            return;
        }
        default:
            break;
    }

    for (auto val : cell_views)
        val->push(event);
}

void CellViewGroup::pushToLogic(const EventPtr event)
{
    cell_interlayer->pushToLogic(event); 
}

void CellViewGroup::draw(RenderTarget& rt)
{
    deleteDeadCells();

    RenderTarget& canvas_rend_target = draw_canvas->getRenderTarget();

    const size_t cell_view_size = cell_views.size();
    for (size_t index = 0; index < cell_view_size; index++)
    {
        if (draw_canvas->isCellVisible(cell_views[index]->getPos(), kCellSize))
            cell_views[index]->draw(canvas_rend_target);
    }
        
    draw_canvas->draw(rt);
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

    SuccessfulCellDeleteEvent* cell_deleted = new SuccessfulCellDeleteEvent();
    cell_interlayer->pushToLogic(cell_deleted);
}

void CellViewGroup::addCell(CellView* cell_view)
{ 
    CellView* casted_cell = reinterpret_cast<CellView*>(cell_view);

    cell_views.push_back(casted_cell);
    casted_cell->setIndexInCellGroup(cell_views.size() - 1);
}

void CellViewGroup::addCell(const FieldType field_type, const Point pos)
{
    cell_interlayer->pushToView(new SmallMapChangedEvent(field_type, pos));
    addCell(CellKeeper::createCellView(field_type, pos, *this));
}
