#pragma once
#include <vector>
#include <functional>
#include <map>
#include <string>
#include <iostream>
#include <typeindex>
#include <typeinfo>
enum class EventType
{
    None = -1,
    Single,
    Persistant,
    Blind,
};

class Event
{
    public:

    protected:
    EventType Type;

};

class EventDispatcher
{
    public:
    
    template <typename T>
    void Dispatch(T& eevee);
    
    
    template <typename T>
    void SubscribeToEvent(std::function<void(T&)> callback);

    
    void UnsubscribeFromEvent();
    
    protected:
    std::unordered_map<std::type_index,std::vector<std::function<void(void*)>>> _CallbackMap; //https://stackoverflow.com/questions/9859390/use-data-type-class-type-as-key-in-a-map !!LYSSNA INTE PÅ DE HÄR -> https://stackoverflow.com/questions/4891511/type-map-in-c 

};

template <typename T>
inline void EventDispatcher::Dispatch(T& eevee)
{
    std::vector<std::function<void(void*)>>& CallbackList = _CallbackMap[std::type_index(typeid(T))]; //gud vilka fel skulle kunda hända här no?, eventpp använder en function som returnar en void ifall den inte existerar
    for (std::function<void(void*)> Listener : CallbackList) 
        Listener(&eevee);
}

template <typename T>
inline void EventDispatcher::SubscribeToEvent(std::function<void(T&)> callback)
{
    std::vector<std::function<void(void*)>>& CallbackList = _CallbackMap[std::type_index(typeid(T))];

    CallbackList.push_back([callback](void* eevee){callback(*static_cast<T*>(eevee));});
}



// switch(Type)
// {
//     case EventType::Single:

//     break;
//     case EventType::Persistant:
    
//     break;
//     case EventType::Blind:
    
//     break;
//     default:
//     return;
    
//}