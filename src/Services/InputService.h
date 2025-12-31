#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
#include "Event.h"
#include "BlehKeys.h"
#include <unordered_map>

enum class KeyAction
{
    None = -1,
    OnKeyPress,
    OnKeyRelease,
    OnKeyRepeat,
};

enum class KeyState
{
    None = -1,
    KeyUp, 
    KeyDown,
};



class KeyEvent : public Event
{
    public:
        inline Bleh::Key GetKeyCode() const { return _KeyCode; }
        KeyEvent(Bleh::Key keyCode) 
            : _KeyCode(keyCode) {}
    protected:
    Bleh::Key _KeyCode;
};
class KeyPressedEvent : public KeyEvent{public: KeyPressedEvent(Bleh::Key keyCode) : KeyEvent(keyCode){}};
class KeyReleasedEvent : public KeyEvent{};
class KeyRepeatEvent : public KeyEvent{};




//GetKeyPress, GetKeyReleased är events
//GetKeyDown, GetKeyUp är polls
//GetKeyPress skickas samtidigt som unordered map uppdateras
class InputService 
{
    public: 
    InputService(GLFWwindow *window);
    
    bool GetKeyDown(Bleh::Key);
    //bool GetKeyUp
    void OnKeyReleased(KeyReleasedEvent& e);
    void OnKeyPressed(KeyPressedEvent& e);
    private:
    static void UpdateKeyMap();
    EventDispatcher _InputDispatcher;
    static void PollKeys(GLFWwindow *window, int key, int scanCode, int action, int modifierBits); // borde man kunna disablea det här asså att programmet inte kollar för keys
    std::unordered_map<Bleh::Key, KeyState> _KeyStateMap;

};

