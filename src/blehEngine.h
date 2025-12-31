#include <GLFW/glfw3.h>
#include "renderer\Renderer.h"
#include "renderer/Texture.h"
#include "services/InputService.h"
#include "Camera.h"
class blehEngine
{
private:
    GLFWwindow* Window;
    void ProcessInput();
    void InitializeGLFW();
    void InitializeGlad();
    void GameLoop(Renderer renderer, Texture texture1, Texture texture2, InputService& inputservice, Camera& camera);
public:
    blehEngine();
    void Initialize();
};