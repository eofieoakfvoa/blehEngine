#include <GLFW/glfw3.h>
#include "renderer\Renderer.h"
#include "renderer/Texture.h"
#include "Services/InputEventSystem.h"
class blehEngine
{
private:
    GLFWwindow* Window;
public:
    blehEngine();
    void ProcessInput();
    void InitializeGLFW();
    void Initialize();
    void GameLoop(Renderer renderer, Texture texture1, Texture texture2);
};