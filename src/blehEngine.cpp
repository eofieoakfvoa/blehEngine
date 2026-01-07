#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <print>

#include "Services/AssetLoader.h"
#include "blehEngine.h"
#include "renderer/Renderer.h"
#include "renderer/Buffers.h"
#include "renderer/Shader.h"
#include "renderer/VertexArrayObject.h"
#include "renderer/Texture.h"
#include "Services/InputService.h"
#include "Camera.h"
#include "blehMath/blehMath.h"

int main()
{
    blehEngine bleh;
    bleh.Initialize();
    return 0;
}


using std::cout;
using std::endl;
//En thread för varje subsystem av programmet, så mainthread är main loop. animation thread dynamics thread rendering thread network thread-

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

void blehEngine::InitializeGLFW()
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
    Window = glfwCreateWindow(800, 600, "blehEngine", NULL, NULL);
    glfwMakeContextCurrent(Window);
    glfwSetFramebufferSizeCallback(Window, framebuffer_size_callback);
    // return Window
}
void blehEngine::InitializeGlad()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        return;
    }
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_DEPTH_TEST);
    
}
#include "Services/Model.h"
void blehEngine::Initialize()
{
    InitializeGLFW();
    InitializeGlad();
    VertexArrayObject VAO;
    VAO.Bind();


    // automate
    /* 
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
    

    VertexBufferObject VBO(vertices, sizeof(vertices)); // automate // vertex size * rows * sizeof(float)
    ElementBufferObject EBO(indices, sizeof(indices));
    */
    // Texture texture1("engineResources/Textures/container.jpg"), texture2("engineResources/Textures/cc12.jpg");
    // Shader shader;
    // ShaderProgramSource Source = shader.ParseShader("engineResources/shaders/defaultShader.shader");

    Texture texture1(ResourcePath"Textures/container.jpg"), texture2(ResourcePath"Textures/cc12.jpg");
    Shader shader;
    ShaderProgramSource Source = shader.ParseShader(ResourcePath"shaders/defaultShader.shader");
    unsigned int realshader = shader.CreateShader(Source.VertexSource, Source.FragmentSource);
    /* 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    */
    Renderer renderer(realshader);
    glUseProgram(realshader);
    shader.setInt("texture1", 0);
    shader.setInt("texture2", 1);
    Camera camera(blehMath::vector3(0.0f,0.0f,0.0f), Camera::EulerToQuaternion(blehMath::vector3(0.0f,0.0f,0.0f)));
    renderer.SetCurrentCamera(&camera);
    InputService InputSystem(Window);
    
    AssetLoader aLoader;
    Mesh newmesh = aLoader.LoadAsset(ResourcePath"temp/newcube.gltf");
    newmesh.CreateVertexArray();
    renderer.AddMesh(newmesh);

    GameLoop(renderer, texture1, texture2, InputSystem, camera);
    glfwDestroyWindow(Window);
    glfwTerminate();
}

void blehEngine::GameLoop(Renderer& renderer, Texture texture1, Texture texture2, InputService& inputsystem, Camera& camera)
{
    while (!glfwWindowShouldClose(Window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        blehMath::vector3 cameraposition = camera.GetPosition();
        if (inputsystem.GetKeyDown(Bleh::Key::W))
        {
            cameraposition = blehMath::vector3(cameraposition.x, cameraposition.y, cameraposition.z - 0.0005f); //fps dependent på hastigheten
            camera.SetPosition(cameraposition);
        }
        if (inputsystem.GetKeyDown(Bleh::Key::A))
        {
            cameraposition = blehMath::vector3(cameraposition.x - 0.0005f, cameraposition.y, cameraposition.z); 
            camera.SetPosition(cameraposition);
    
        }
        if (inputsystem.GetKeyDown(Bleh::Key::S))
        {
            cameraposition = blehMath::vector3(cameraposition.x, cameraposition.y, cameraposition.z + 0.0005f); 
            camera.SetPosition(cameraposition);
        }
        if (inputsystem.GetKeyDown(Bleh::Key::D))
        {
            cameraposition = blehMath::vector3(cameraposition.x + 0.0005f, cameraposition.y, cameraposition.z); 
            camera.SetPosition(cameraposition);
        }

        texture1.SetActive(GL_TEXTURE0);
        texture2.SetActive(GL_TEXTURE1);
        camera.LookAt(camera.GetPosition() + camera.CameraFront); 
        
        renderer.RenderFrame();
        
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glfwSwapBuffers(Window);
        glfwPollEvents();
    }
}
