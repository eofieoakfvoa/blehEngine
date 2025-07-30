#include "InputEventSystem.h"
#include <iostream>
void InputEventSystem::FireInputEvent(int key)
{
    
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
    else if (Action == GLFW_REPEAT) // ska inte kollas ifall den hålls ner mest bara för typing lowkey
    {
        std::cout << "Key " << Key << " Held!\n";
    } 
    // på något sätt när en knapp blir klickad så

    //void ToggleContinousHold(int Key, bool Toggle)
    //{

    //}
}