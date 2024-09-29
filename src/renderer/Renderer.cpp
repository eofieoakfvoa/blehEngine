#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Renderer::Renderer(unsigned int shader)
    : UniformLocation(glGetUniformLocation(shader, "_Color")), shaderID(shader)
{
}

Renderer::~Renderer()
{
}

void Renderer::RenderFrame()
{
    glUseProgram(shaderID);
    glUniform4f(UniformLocation, 0.0f, 0.3f, 0.8f, 0.8f);
}