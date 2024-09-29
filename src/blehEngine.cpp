#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "blehEngine.h"
#include "renderer/Renderer.h"
#include "renderer/Buffers.h"
#include "renderer/Shader.h"
#include "renderer/VertexArrayObject.h"

using std::cout;
using std::endl;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void blehEngine::Initialize()
{
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    // glEnable(GL_DEBUG_OUTPUT);

    GLFWwindow *window;
    window = glfwCreateWindow(800, 600, "blehEngine", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        return;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // automate
    float vertices[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] =
    { 
        0, 1, 3,
        1, 2, 3
    };
    
    VertexArrayObject VAO;
    ElementBufferObject EBO(indices, sizeof(indices));
    VertexBufferObject VBO(vertices, 3 * 4 * sizeof(float)); // automate // vertex size * rows * sizeof(float)
    
    glEnableVertexAttribArray(0); 
    
    Shader shader;
    ShaderProgramSource Source = shader.ParseShader("src/res/shaders/defaultShader.shader");
    unsigned int realshader = shader.CreateShader(Source.VertexSource, Source.FragmentSource);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); // automate
    
    
    Renderer renderer(realshader);

    GameLoop(window, renderer);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void blehEngine::GameLoop(GLFWwindow *window, Renderer renderer)
{
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.RenderFrame();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // automate

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main()
{
    blehEngine bleh;
    bleh.Initialize();
    return 0;
}