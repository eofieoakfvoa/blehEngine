#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "blehEngine.h"
#include "renderer/Renderer.h"
#include "renderer/Buffers.h"
#include "renderer/Shader.h"
#include "renderer/VertexArrayObject.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer/Texture.h"
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
    //     float vertices[] = {
    // //       {--POSITIONS--}      {--COLORS--}       (--TEXCORDS--)
    //         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
    //         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    //         -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    //         -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    //     };
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
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
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

    // float vertices[] = {
    //     0.25f,  0.25f, 0.0f, // top right
    //     0.25f, -0.25f, 0.0f, // bot right
    //     -0.25f, -0.25f, 0.0f, // bot left
    //     -0.25f,  0.25f, 0.0f, // top left
    //     -0.75f,  0.25f, 0.0f,
    //     -0.75f,  -0.25f, 0.0f
    // };
    // unsigned int indices[] =
    // {
    //     0, 1, 3,
    //     1, 2, 3,
    //     2,3,4,
    //     2,4,5
    // };
    unsigned int indices[] =
        {
            0, 1, 3,
            1, 2, 3};
    VertexArrayObject VAO;
    VertexBufferObject VBO(vertices, sizeof(vertices)); // automate // vertex size * rows * sizeof(float)
    ElementBufferObject EBO(indices, sizeof(indices));

    Texture texture1("src/res/Textures/container.jpg");
    Texture texture2("src/res/Textures/cc12.jpg");
    Shader shader;
    ShaderProgramSource Source = shader.ParseShader("src/res/shaders/defaultShader.shader");
    unsigned int realshader = shader.CreateShader(Source.VertexSource, Source.FragmentSource);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Renderer renderer(realshader);
    glUseProgram(realshader);
    glUniform1i(glGetUniformLocation(realshader, "texture1"), 0);
    glUniform1i(glGetUniformLocation(realshader, "texture2"), 1);

    GameLoop(window, renderer, texture1.GetRenderID(), texture2.GetRenderID());

    glfwDestroyWindow(window);
    glfwTerminate();
}

void blehEngine::GameLoop(GLFWwindow *window, Renderer renderer, unsigned int texture1, unsigned int texture2)
{
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        renderer.RenderFrame();
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); // automate
        glDrawArrays(GL_TRIANGLES, 0, 36);
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