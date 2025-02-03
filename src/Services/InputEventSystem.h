#include <GLFW/glfw3.h>
#include <unordered_map>
//#include <functional>
#include <iostream>
#include <memory>
#include <vector>
//ref https://denyskryvytskyi.github.io/event-system
//ref https://gameprogrammingpatterns.com/event-queue.html

#pragma once


enum KeyStates
{
    KeyPressed, // Skickar en gång när knappen först blir klickad. 
    KeyReleased, // Skickar en gång när knappen blir släppt.
    KeyContinuous, // Skickas constant medans knappen är nere. + multiple
    KeyRepeat, // Basic Windows repeat altså blir det en delay, borde användas för typing. + Inte multiple
};
class InputEvent
{
    public:
        bool Handled = false;
};
//using EventHandler = std::function<void(const InputEvent& e)>;
class InputEventWrapper
{
    private:
    void Call()
    {
        //std::function<void(const InputEvent& e)>;
    }
    public:
    void Execute()
    {
        Call();
    }
};
class InputEventSystem
{
    private:
        void FireInputEvent(int key);
        void DispatchInputEvent();
    public:
        InputEventSystem(GLFWwindow* Window);
        static void KeyCallBack(GLFWwindow* Window, int Key, int scanCode, int Action, int Mods);
};