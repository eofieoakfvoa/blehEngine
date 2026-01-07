#pragma once
#include "Camera.h"
#include "Services/Model.h"
#include <vector>

enum RendererApiType
{
    None,
    OpenGL,
    Vulkan,
};

class Renderer
{
public:
    Renderer(unsigned int shader);
    ~Renderer();
    void RenderFrame();
    void SetCurrentCamera(Camera* cameraToBeSet);
    Camera& GetCurrentCamera();
    void AddMesh(Mesh& mesh);
private:
    std::vector<Mesh> _Meshes; 
    int UniformLocation;
    unsigned int shaderID;
    Camera* currentCamera;
};