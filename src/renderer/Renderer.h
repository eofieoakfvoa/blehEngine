#pragma once
#include "Camera.h"
#include "Services/Assets/Model.h"
#include <vector>
#include <memory>
namespace bleh
{
class AssetManager;
    
    class Renderer
    {
        public:
            Renderer();
            ~Renderer();
    
            void RenderFrame(); 
            void AddMesh(std::shared_ptr<Mesh> mesh);
    
            void SetShader(uint32_t shader);
            void SetCurrentCamera(Camera* cameraToBeSet);
            Camera& GetCurrentCamera();
            std::weak_ptr<AssetManager> assetmanager;
        
        private:

            int _UniformLocation; //tror varje window ska ha en renderer själv, så kan jag typ göra så renderer kan vara specifikt för ui för debugging
            uint32_t _shaderID;

            Camera* _currentCamera = nullptr;
            std::vector<std::shared_ptr<Mesh>> _Meshes;
    };
}