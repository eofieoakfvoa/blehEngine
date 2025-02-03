#include "InputEventSystem.h"
#include <iostream>
void InputEventSystem::FireInputEvent(int key)
{
    auto it = _Subscribers.find(key);
    if (it != _Subscribers.end())
    {
        for (auto& wrapper : it->second)
        {
            wrapper->Execute();
        }
    }
}
void InputEventSystem::DispatchInputEvent()
{
}
InputEventSystem::InputEventSystem(GLFWwindow *Window)
{
    glfwSetKeyCallback(Window, KeyCallBack);
}

void InputEventSystem::KeyCallBack(GLFWwindow* Window, int Key, int scanCode, int Action, int Mods)
{
    auto* inputSystem = static_cast<InputEventSystem*>(glfwGetWindowUserPointer(Window));
    if (Action == GLFW_PRESS)
    {
        std::cout << "Key " << Key << " pressed!\n";
        inputSystem->FireInputEvent(Key);
    }
    else if (Action == GLFW_RELEASE)
    {
        std::cout << "Key " << Key << " released!\n";
    }    
    else if (Action == GLFW_REPEAT) // använd it detta eftersom den kollar bara ifall en knapp repeatar så jag borde igentligen kolla ifall den blev released efter ha blivit klickd
    {
        std::cout << "Key " << Key << " Held!\n";
    }
}

void InputEventSystem::SubscribeToInput(const int key)
{
    auto wrapper = std::make_unique<InputEventWrapper>();
    _Subscribers[key].push_back(std::move(wrapper));
}
