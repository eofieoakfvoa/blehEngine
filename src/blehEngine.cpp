#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include "blehEngine.h"
#include "renderer/Renderer.h"
#include "renderer/Buffers.h"
#include "renderer/Shader.h"
#include "renderer/VertexArrayObject.h"
#include "renderer/Texture.h"
#include "Services/InputEventSystem.h"
using std::cout;
using std::endl;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

blehEngine::blehEngine()
{
}

void blehEngine::ProcessInput()
{
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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    // glEnable(GL_DEBUG_OUTPUT);
    // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    Window = glfwCreateWindow(800, 600, "blehEngine", NULL, NULL);
    if (Window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        return;
    }

    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);

    // automate

    float vertices[] =
        {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
        };
    unsigned int indices[] =
        {
            0, 1, 3,
            1, 2, 3
        };
    VertexArrayObject VAO;
    VertexBufferObject VBO(vertices, sizeof(vertices)); // automate // vertex size * rows * sizeof(float)
    ElementBufferObject EBO(indices, sizeof(indices));

    Texture texture1("src/res/Textures/container.jpg"), texture2("src/res/Textures/cc12.jpg");
    Shader shader;
    ShaderProgramSource Source = shader.ParseShader("src/res/shaders/defaultShader.shader");
    unsigned int realshader = shader.CreateShader(Source.VertexSource, Source.FragmentSource);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Renderer renderer(realshader);
    glUseProgram(realshader);
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    InputEventSystem InputSystem(Window);

    GameLoop(renderer, texture1, texture2);
    glfwDestroyWindow(Window);
    glfwTerminate();
}

void blehEngine::GameLoop(Renderer renderer, Texture texture1, Texture texture2)
{
    while (!glfwWindowShouldClose(Window))
    {
        // Game Pipeline?
        // Input
        // Physics
        // render Pipeline
        ProcessInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        texture1.SetActive(GL_TEXTURE0);
        texture2.SetActive(GL_TEXTURE1);

        renderer.RenderFrame();
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // automate
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
}

int main()
{
    blehEngine bleh;
    bleh.Initialize();
    return 0;
}