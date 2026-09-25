#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

namespace bleh
{
    
    class WindowSize
    {
        public: 
            int Width;
            int Height;
    };
    class WindowSpecifications
    {
        public:
            std::string Title;
            WindowSize Size;
    };


    class Window
    {
        public:
            
            Window(WindowSpecifications windowspec, GLFWwindow* ShareContext = nullptr);
            ~Window();
            
            Window(const Window&) = delete;
            Window& operator=(const Window&) = delete;

            Window(Window&& other) noexcept;
            Window& operator=(Window&& other) noexcept;

            GLFWwindow* GetWindow();
            WindowSize GetWindowSize();

        private:
            static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
            GLFWwindow* _windowInstance;
    
    };
    

}