#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <print>
#include <cstdint>
#include <memory>

#include "blehEngine.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/VertexArrayObject.h"
#include "Services/InputService.h"
#include "errorReporting.h"
#include "Services/BlehKeys.h"
#include "Services/blehServices.h"


//void* operator new(size_t size)
//{
//    std::println("Allocating : {} Bytes", size);
//    return malloc(size);
//}
//void operator delete(void* memory,size_t size)
//{
//    std::println("freeing : {} Bytes", size);
//    free(memory);
//}

namespace bleh
{



    void blehEngine::Initialize()
    {
        if (!glfwInit())
        {
            std::println("Failed to initialize GLFW");
            return;
        }


        _WindowManager = std::make_unique<WindowManager>();
        uint8_t windowHandle;
        _WindowManager->CreateWindow(WindowSpecifications("blehEngine", WindowSize(800, 600)), windowHandle);
        uint8_t debugWindowHandle;
        _WindowManager->CreateWindow(WindowSpecifications("Debug Window", WindowSize(800, 600)), debugWindowHandle, windowHandle);

        //uint8_t debugWindowHandle2;
        //_WindowManager->CreateWindow(WindowSpecifications("Debug Window2", WindowSize(800, 600)), debugWindowHandle2, windowHandle);
        _WindowManager->SetActiveWindow(windowHandle);

        //dessa vill jag ha bort
        _Window = _WindowManager->GetWindowByHandle(0).GetWindow();
        enableReportGlErrors(); 
        VertexArrayObject VAO;
        VAO.Bind();
        


        _Renderer = std::make_unique<Renderer>();
        _BlehServices = std::make_unique<blehServices>(); 
        _inputService = std::make_unique<InputService>(_Window); 
    


        //borde va default i manager class ... Alltså att den inte skapas här istället någon annan stans
        Shader shader;
        ShaderProgramSource Source = shader.ParseShader(ResourcePath "shaders/defaultShader.shader");
        uint32_t realshader = shader.CreateShader(Source.VertexSource, Source.FragmentSource);
        _Renderer->SetShader(realshader);
        glUseProgram(realshader);
        shader.setInt("texture1", 0);
        shader.setInt("texture2", 1);
    

        //[[-- Helst ska alla sub systems ha en Initialize eftersom jag är fortfarande inte säker ifall de ska vara static eller inte, och ifall jag då gör de till static så är Initialize() och Shutdown bättre än constructor och deconstructor iaf när det var skrivet? --]]
        _BlehServices->Initialize(*_Renderer, *_inputService);
        _BlehGame->setBlehServices(*_BlehServices);
        _BlehGame->Initialize();

        _GameLoop();

        glfwDestroyWindow(_Window);
        glfwTerminate();


        //beautiful martyr dont u know id do anything for u
    }

    void blehEngine::_GameLoop()
    {
        while (!glfwWindowShouldClose(_Window))
        {

            glfwPollEvents();

            _BlehGame->OnUpdate();  

            //per window
            int i = 1;
            for (Window& currentWindow : _WindowManager->GetAllWindows())
            {
                std::println("{}", i);
                i++;
                GLFWwindow* windowInstance = currentWindow.GetWindow();
                glfwMakeContextCurrent(windowInstance);
                
                
                if (_inputService->GetKeyDown(bleh::Key::ESCAPE)) //kanske inom window eller inputservice och borde använda engine kod med subscribe istället för getkeydown
                {
                    glfwSetInputMode(windowInstance, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

                }
                if (_inputService->GetInputClick(bleh::Key::Mouse_Left))
                {
                    glfwSetInputMode(windowInstance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

                }

                if (_inputService->GetInputClick(bleh::Key::X))
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
 

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                _Renderer->RenderFrame();

                glfwSwapBuffers(windowInstance);

            }


        }
    }
}

