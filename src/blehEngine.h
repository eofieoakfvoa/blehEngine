#include <GLFW/glfw3.h>
#include "renderer\Renderer.h"
class blehEngine
{
    public: 
        void Initialize();
        void GameLoop(GLFWwindow* window, Renderer renderer, unsigned int texture1, unsigned int texture2);
};