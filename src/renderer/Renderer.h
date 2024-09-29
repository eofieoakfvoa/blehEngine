#pragma once

class Renderer
{
private:
    int UniformLocation;
    unsigned int shaderID;

public:
    Renderer(unsigned int shader);
    ~Renderer();
    void RenderFrame();
};