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
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::RenderFrame()
    {

        glUseProgram(_shaderID);
        if (!_currentCamera)
        {
            std::println("NO CAMERA ACTIVE");
            return;
        }

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
                    if (meshParts.TextureHandle.UUID != 0)
                    {
                        lockedAssetManager->SetTextureActive(meshParts.TextureHandle.UUID, 0);
                    }
                    else
                    {
                
                    }
                }
                meshParts.VertexArray.Bind();
                glDrawElements(meshParts.Mode, meshParts._IndexCount , meshParts._IndexType, (void*)(intptr_t)meshParts._IndicesByteOffset);
            }
        }


    }

    void Renderer::SetShader(uint32_t shader)
    {
        _UniformLocation = glGetUniformLocation(shader, "_Color");
        _shaderID = shader;
    }

    void Renderer::SetCurrentCamera(Camera *cameraToBeSet) // borde probably ha en lista eller något ifall det finns flera kameror
    {
        _currentCamera = cameraToBeSet;
    }

    Camera &Renderer::GetCurrentCamera()
    {
        return *_currentCamera;
    }

    void Renderer::AddMesh(std::shared_ptr<Mesh> mesh)
    {
        _Meshes.emplace_back(mesh);
    } 
}
