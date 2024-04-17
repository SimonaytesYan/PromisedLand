#pragma once

#include "../Events/Eventable.hpp"
#include "../../StlVector/Src/Vector.hpp"

// Event owner 
class EventHolder
{
public: 
    EventHolder(Event* event, int counter = 0, bool active = true) :
    counter (counter),
    event   (event),
    active  (active)
    { }

    EventHolder(const EventHolder& event_ptr) :
    active  (event_ptr.active),
    counter (event_ptr.counter),
    event   (event_ptr.event)
    { }

    void addRef()
    { counter++; }

    void removeRef()
    { counter--; }

    bool getActive()
    { return active; }
    
    void invalid()
    { active = false; }

    void setActive(const bool new_value)
    { active = new_value; }

    int getCounter()
    { return counter; }

    Event* getPtr()
    { return event; }


    ~EventHolder()
    { delete event; }

private:
    bool   active;
    int    counter;
    Event* event;
};

class EventPtr
{   
public:
    EventPtr(Event* event)
    : event_holder (new EventHolder(event)),
      event        (event_holder->getPtr())
    { }

    EventPtr(const EventPtr& event_ptr) :
    event_holder (event_ptr.event_holder)
    {
        event_holder->addRef();
    }

    EventPtr(EventPtr&& event_ptr) :
    event_holder (event_ptr.event_holder)
    { }
    
    EventPtr& operator=(const EventPtr& other)
    {
        event_holder->removeRef();
        if (event_holder->getCounter() == 0)
            delete event_holder;

        event_holder = other.event_holder;
        event_holder->addRef();

        return *this;
    }

    ~EventPtr()
    {
        event_holder->removeRef();
        if (event_holder->getCounter() == 0)
            delete event_holder;
    }

    Event* operator->()
    { return event; }

    Event* operator()()
    { return event; }

    Event* get()
    { return event; }

    const Event* operator->() const
    { return event; }

    const Event* operator()() const
    { return event; }

    const Event* get() const
    { return event; }

    bool active()
    { return event_holder->getActive(); }
    
    void setActive(const bool new_value)
    { event_holder->getActive(); }

private:
    EventHolder* event_holder;
    Event*       event;    
};

