#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Event.h"
#include "BlehKeys.h"

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
class KeyReleasedEvent : public KeyEvent{public: KeyReleasedEvent(Bleh::Key keyCode) : KeyEvent(keyCode){}};
class KeyRepeatEvent : public KeyEvent{};


class InputService 
{
    public: 
    InputService(GLFWwindow *window);
    
    bool GetKeyDown(Bleh::Key);
    bool GetKeyUp(Bleh::Key);
    void OnKeyReleased(KeyReleasedEvent& e);
    void OnKeyPressed(KeyPressedEvent& e);

    private:
    
    EventDispatcher _InputDispatcher;
    static void PollKeys(GLFWwindow *window, int key, int scanCode, int action, int modifierBits); // borde man kunna disablea det här asså att programmet inte kollar för keys
    std::unordered_map<Bleh::Key, KeyState> _KeyStateMap;

};

