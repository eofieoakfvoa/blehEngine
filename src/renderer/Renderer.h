#pragma once
#include "Camera.h"
enum RendererApiType
{
    None,
    OpenGL,
    Vulkan,
};

class Renderer
{
private:
    int UniformLocation;
    unsigned int shaderID;
    Camera* currentCamera;
public:
    Renderer(unsigned int shader);
    ~Renderer();
    void RenderFrame();
    void SetCurrentCamera(Camera* cameraToBeSet);
    Camera& GetCurrentCamera();
};