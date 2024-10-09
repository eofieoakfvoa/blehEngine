#include <GLFW/glfw3.h>
#include "renderer\Renderer.h"
#include "renderer/Texture.h"
#include "Services/InputEventSystem.h"
class blehEngine
{
    public: 
        void Initialize();
        void GameLoop(GLFWwindow* window, Renderer renderer, Texture texture1, Texture texture2, InputEventSystem* inputsystem);
};