#pragma once

#include <GLFW/glfw3.h>
#include <vector>
#include <functional>
#include "Event.h"

enum class KeyAction
{
    None = -1,
    OnKeyPress,
    OnKeyRelease,
    OnKeyHeld
};

class InputEvent : public Event
{
public:
    InputEvent(GLFWwindow* window);

    // Subscribes a listener to the key input events
    void SubscribeToEvent(std::function<void(KeyAction, int)> function);

    // This will be called by GLFW
    static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);

private:
    // Dispatches the key event to all listeners
    void DispatchEvent(KeyAction keyAction, int key);

    std::vector<std::function<void(KeyAction, int)>> listeners;
};
