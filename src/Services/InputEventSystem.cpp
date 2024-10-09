#include "InputEventSystem.h"
#include <iostream>
InputEventSystem::InputEventSystem(GLFWwindow* Window)
{
    glfwSetKeyCallback(Window, KeyCallBack);
}

void InputEventSystem::KeyCallBack(GLFWwindow* Window, int Key, int scanCode, int Action, int Mods)
{
    if (Action == GLFW_PRESS)
    {
        std::cout << "Key " << Key << " pressed!\n";
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

