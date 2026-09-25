#include "Window.h"
#include <print>
namespace bleh
{

        
    Window::Window(WindowSpecifications windowspec, GLFWwindow* ShareContext)
    {

        // gör som WindowSpecifictaions fast för OpenGL, fast typ efter jag gjort allt i PLATFORM
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

        _windowInstance = glfwCreateWindow(windowspec.Size.Width, windowspec.Size.Height, windowspec.Title.c_str(), nullptr, ShareContext);
        
        glfwSetFramebufferSizeCallback(_windowInstance, framebuffer_size_callback);

        
        if (_windowInstance == NULL)
        {
            std::println("Failed to open GLFW window");
            glfwTerminate();
            return;
        }

    }

    Window::~Window()
    {
        if (_windowInstance)
            glfwDestroyWindow(_windowInstance);
    }

    Window::Window(Window&& other) noexcept
        : _windowInstance(other._windowInstance)
    {
        other._windowInstance = nullptr;
    }

    Window& Window::operator=(Window&& other) noexcept
    {
        if (this != &other)
        {
            if (_windowInstance)
                glfwDestroyWindow(_windowInstance);
            
            _windowInstance = other._windowInstance;
            other._windowInstance = nullptr;
        }
        return *this;
    }

    GLFWwindow* Window::GetWindow()
    {
        return _windowInstance; 
    }

    WindowSize Window::GetWindowSize()
    {
        int width, height;
        glfwGetWindowSize(_windowInstance, &width, &height);
        return WindowSize{ .Width = width, .Height = height};
    }
    void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glfwMakeContextCurrent(window);
        glViewport(0, 0, width, height);
    }
}
