#include "Event.h"

Event::Event(EventType type)
    :Type(type)
    {}



void Event::DispatchEvent()
{
    switch(Type)
    {
        case Single:
            for (std::function<void()> Listener : Listeners)
                Listener();
            break;
        case Persistant: 

            break;
        case Blind:

            break;
        default:
            return;
        
    }
}

void Event::SubscribeToEvent(std::function<void()> function)
{
    Listeners.push_back(function);
}
