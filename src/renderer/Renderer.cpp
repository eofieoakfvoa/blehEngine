#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>

Renderer::Renderer(unsigned int shader)
    : UniformLocation(glGetUniformLocation(shader, "_Color")), shaderID(shader)
{
}

Renderer::~Renderer()
{
}

void Renderer::RenderFrame()
{
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    glUseProgram(shaderID);
    glUniform4f(UniformLocation, 0.0f, greenValue, 0.8f, 0.8f);
}