#include "Window.h"

Window::Window(std::string Title, int ResolutionWidth, int ResolutionHeight)
    : _windowInstance(glfwCreateWindow(ResolutionWidth, ResolutionHeight, Title.c_str(), nullptr, nullptr))
{
    if (_windowInstance == NULL)
    {
        std::cout << "Failed to open GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    
}

GLFWwindow* Window::GetWindow()
{
    return _windowInstance; // fixa så att ifall det inte finns så skapas en
}
