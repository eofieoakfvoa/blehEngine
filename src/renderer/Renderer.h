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
            void SetFallBackTexturetemp(blehHandle texture);
        private:
            void _ScreenPass();
            int _UniformLocation; 
            uint32_t _shaderID;
            std::vector<FrameBufferObject> FrameBufferStorage;
            Camera* _currentCamera = nullptr;
            std::vector<std::shared_ptr<Mesh>> _Meshes;
            uint32_t fullscreentriangle;
            blehHandle _FallbackTexture;
    };
}