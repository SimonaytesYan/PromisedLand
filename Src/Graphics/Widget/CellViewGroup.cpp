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
            addCell(build_event->cell_type, build_event->pos);
            
            break;
        }  
        case EventType::DESTROY_CELL_VIEW_EVENT:
        {  
            const DestroyCellViewEvent* delete_event = static_cast<const DestroyCellViewEvent*>(event.get());
            delete_event->cell_view->kill();
            
            size_t index = 0;
            for (index = 0; index < cell_views.size(); index++)
            {
                if (cell_views[index] == delete_event->cell_view)
                    break;
            }
            cell_interlayer->pushToLogic(new DestroyCellLogicEvent(index));
            
            break;
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

void CellViewGroup::addCell(CellView* cell_view)
{ 
    cell_views.push_back(cell_view);
    cell_view->setIndexInCellGroup(cell_views.size() - 1);
}

void CellViewGroup::addCell(const Texture texture, const Point pos)
{
    const size_t index = cell_views.size();
    cell_views.push_back(new CellView(texture, pos, *this, index));
}

void CellViewGroup::addCell(const FieldType field_type, const Point pos)
{
    switch (field_type)
    {
        case FieldType::Grass:
            addCell(new GrassView(pos, *this));
            break;
        case FieldType::Water:
            addCell(new WaterView(pos, *this));
            break;
        case FieldType::House:
            addCell(new HouseView(pos, *this));
            break;
        case FieldType::Sawmill:
            addCell(new SawmillView(pos, *this));
            break;
        case FieldType::Well:
            addCell(new WellView(pos, *this));
            break;
        case FieldType::Windmill:
            addCell(new WindmillView(pos, *this));
            break;
        default:
            break;
    }
}
