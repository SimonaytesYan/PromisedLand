#pragma once

#include "Events.hpp"
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
    // Get Event*, allocated with new
    EventPtr(Event* event)
    : event_holder (new EventHolder(event)),
      event        (event)
    { event_holder->addRef(); }

    EventPtr(const EventPtr& other) 
    : event_holder (other.event_holder),
      event        (other.event)
    { event_holder->addRef(); }

    EventPtr(EventPtr&& other) 
    : event_holder (other.event_holder),
      event        (other.event)
    { event_holder->addRef(); }
    
    EventPtr& operator=(const EventPtr& other)
    {
        if (other.event_holder == event_holder)
            return *this;

        event_holder->removeRef();
        if (event_holder->getCounter() == 0)
            delete event_holder;

        event_holder = other.event_holder;
        event        = other.event;
        event_holder->addRef();

        return *this;
    }

    EventPtr& operator=(EventPtr&& other)
    {
        Swap(event_holder, other.event_holder);
        Swap(event,        other.event);

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

