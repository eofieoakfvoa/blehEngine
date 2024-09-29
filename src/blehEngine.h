#include <GLFW/glfw3.h>
#include "renderer\Renderer.h"
class blehEngine
{
    public: 
        void Initialize();
        void GameLoop(GLFWwindow* window, Renderer renderer);
};