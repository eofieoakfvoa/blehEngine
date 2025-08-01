#include "InputService.h"
#include <iostream>

InputEvent::InputEvent(GLFWwindow* window)
    : Event(EventType::Single)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, KeyCallback);
}

void InputEvent::SubscribeToEvent(std::function<void(KeyAction, int)> function)
{
    listeners.push_back(function);
}

void InputEvent::DispatchEvent(KeyAction keyAction, int key)
{
    for (const auto& listener : listeners)
    {
        listener(keyAction, key);
    }
}

void InputEvent::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    auto* inputSystem = static_cast<InputEvent*>(glfwGetWindowUserPointer(window));

    switch (action)
    {
    case GLFW_PRESS:
        std::cout << "Key " << key << " pressed!\n";
        inputSystem->DispatchEvent(KeyAction::OnKeyPress, key);
        break;

    case GLFW_RELEASE:
        std::cout << "Key " << key << " released!\n";
        inputSystem->DispatchEvent(KeyAction::OnKeyRelease, key);
        break;

    case GLFW_REPEAT:
        std::cout << "Key " << key << " held!\n";
        inputSystem->DispatchEvent(KeyAction::OnKeyHeld, key);
        break;
    }
}
