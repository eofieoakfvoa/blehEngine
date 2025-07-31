#pragma once
#include <vector>
#include <functional>
#include <map>
#include <string>
enum EventType
{
    None = -1,
    Single, //function calls
    Persistant, //eventet sparas, t.ex för att skicka delayed events eller kopiera events
    Blind // eventet skickar event till något som skickar vidare
};

class Event
{
    public:
    
    Event(EventType type);
    void DispatchEvent();
    virtual void SubscribeToEvent(std::function<void()> callback);
    protected:
    std::vector<std::function<void()>> Listeners;
    //std::map<std::string, > EventArgs; Fixa senare
    EventType TypeOfEvent;
    //InputEvent::OnEvent(OnKeyRelease, blehKey.W)
};