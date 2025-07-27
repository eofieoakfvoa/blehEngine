#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
class Window
{
private:
    GLFWwindow* _windowInstance;
    
public:
    Window(std::string windowTitle, int windowWidth, int windowHeight);
    ~Window();
    GLFWwindow* GetWindow();
};