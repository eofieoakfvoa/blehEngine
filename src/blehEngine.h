#include <GLFW/glfw3.h>
#include "renderer\Renderer.h"
#include "renderer/Texture.h"
class blehEngine
{
private:
    GLFWwindow* Window;
    void ProcessInput();
    void InitializeGLFW();
    void InitializeGlad();
    void GameLoop(Renderer renderer, Texture texture1, Texture texture2);
public:
    blehEngine();
    void Initialize();
};