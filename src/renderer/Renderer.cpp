#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <Services/InputService.h>
#include <print>
#include <memory>
#include "Services/Assets/AssetManager.h"
namespace bleh
{
    using namespace bleh::gltf;
    Renderer::Renderer()
    {
        FrameBufferStorage.emplace_back(FrameBufferSpecifications(800, 600));
        Shader shader;
        ShaderProgramSource Source = shader.ParseShader(ResourcePath "shaders/screenpass.shader");
        fullscreentriangle = shader.CreateShader(Source.VertexSource, Source.FragmentSource);




    }

    Renderer::~Renderer()
    {
    }


    void Renderer::RenderFrame()
    {
        if (!_currentCamera)
        {
            std::println("NO CAMERA ACTIVE");
            return;
        }

        FrameBufferStorage[0].Bind();
        glViewport(0, 0, FrameBufferStorage[0].Specifications.Width, FrameBufferStorage[0].Specifications.Height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(_shaderID);


        glm::mat4 view = _currentCamera->GetCameraMatrix();
        glm::mat4 projection = _currentCamera->GetProjectionMatrix(); // finns ingen anledning att få denna varje frame, där den basically bara kommer ändras när skärmen resizar
        uint32_t viewLocation = glGetUniformLocation(_shaderID, "view");
        uint32_t projectionLocation = glGetUniformLocation(_shaderID, "projection");
        glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1i(glGetUniformLocation(_shaderID, "texture1"), 0);
        glUniform1i(glGetUniformLocation(_shaderID, "texture2"), 1);


        for (std::shared_ptr<Mesh> mesh : _Meshes)
        {
    
            uint32_t modelLocation = glGetUniformLocation(_shaderID, "model");
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mesh->GetModelMatrix()));
            //std::cout << mesh.GetIndexCount() << std::endl;
            //std::cout << mesh.GetIndexType() << std::endl;
            

        
            for (Primative& meshParts : mesh->meshParts)
            {
                if (std::shared_ptr<AssetManager> lockedAssetManager = assetmanager.lock())
                {
                    //std::println("UUUID = {}", meshParts.TextureHandle.UUID);
                    if (meshParts.TextureHandle.UUID != 0)
                    {
                        lockedAssetManager->SetTextureActive(meshParts.TextureHandle.UUID, 0);
                    }
                    else
                    {
                        lockedAssetManager->SetTextureActive(_FallbackTexture.UUID, 0);
                    }
                }
                meshParts.VertexArray.Bind();
                glDrawElements(meshParts.Mode, meshParts._IndexCount , meshParts._IndexType, (void*)(intptr_t)meshParts._IndicesByteOffset);
            }
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTextureUnit(0, FrameBufferStorage[0].GetColorHandle());

        _ScreenPass();
        
    }

    

    void Renderer::_ScreenPass()
    {

        glViewport(0, 0, 800, 600);
        glDisable(GL_DEPTH_TEST);
        glUseProgram(fullscreentriangle);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glEnable(GL_DEPTH_TEST);


    }


    void Renderer::AddMesh(std::shared_ptr<Mesh> mesh)
    {
        _Meshes.emplace_back(mesh);
    } 
    void Renderer::SetShader(uint32_t shader)
    {
        _UniformLocation = glGetUniformLocation(shader, "_Color");
        _shaderID = shader;
    }
    void Renderer::SetFallBackTexturetemp(blehHandle texture)
    {
        _FallbackTexture = texture;
    }

    void Renderer::SetCurrentCamera(Camera *cameraToBeSet) // borde probably ha en lista eller något ifall det finns flera kameror
    {
        _currentCamera = cameraToBeSet;
    }

    Camera &Renderer::GetCurrentCamera()
    {
        return *_currentCamera;
    }

}
