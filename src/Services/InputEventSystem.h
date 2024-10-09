#include <GLFW/glfw3.h>
#pragma once
enum KeyStates
{
    KeyPressed, KeyReleased, KeyHeldDown,
};
class InputEventSystem
{
    private:
    public:
        InputEventSystem(GLFWwindow* Window);
        static void KeyCallBack(GLFWwindow* Window, int Key, int scanCode, int Action, int Mods);

};