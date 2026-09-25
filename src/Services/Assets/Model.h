#pragma once
#include <vector>
#include <iostream>
#include <Services/Assets/gltfinformation.h>
#include <renderer/Buffers.h>
#include <renderer\VertexArrayObject.h>
#include <blehMath/blehMath.h>
#include <Services/Assets/handle.h>
namespace bleh
{
    class Model 
    {
        public:
        Model();
        ~Model();
    
    
    
        private:
        //std::vector<Mesh> _meshes;
    
    };





    class Mesh
    {
        public:
            inline Mesh() : _ModelMatrix(1.0) {}
    
            ~Mesh();
    
    
            blehHandle handle;
            inline const std::vector<gltf::Buffer>& GetBuffers() const { return _Buffers; }
            inline const std::vector<gltf::BufferView>& GetBufferViews() const { return _BufferViews; }
            inline const std::vector<gltf::Accessor>& GetAccessors() const { return _Accessors; }
            inline const std::vector<gltf::Image>& GetImages() const { return _Images; }
            inline const std::vector<gltf::Material>& GetMaterials() const { return _Materials; }
            inline const blehMath::mat4& GetModelMatrix() const { return _ModelMatrix; }
    
            void AddBuffer(gltf::Buffer buffer){_Buffers.emplace_back(buffer); }
            void AddBufferView(gltf::BufferView bufferview){_BufferViews.emplace_back(bufferview); }
            void AddAccessor(gltf::Accessor accessor) { _Accessors.emplace_back(accessor); }
            void AddMeshPart(gltf::Primative meshpart) { meshParts.emplace_back(meshpart); }
            void AddImage(gltf::Image meshpart) { _Images.emplace_back(meshpart); }
            void AddMaterial(gltf::Material meshpart) { _Materials.emplace_back(meshpart); }


            void AddMaterial(blehHandle meshpart){ _ImageHandles.emplace_back(meshpart); }

    


            void print();


            void CreateVertexArray();
    
            std::vector<gltf::Primative> meshParts;
            std::filesystem::path filepath;
            //temp
            blehHandle BaseTexture;
        private:


            std::vector<gltf::Material> _Materials;
            std::vector<gltf::Image> _Images;
            std::vector<blehHandle> _ImageHandles;
            std::vector<gltf::Buffer> _Buffers;
            std::vector<gltf::BufferView> _BufferViews;
            std::vector<gltf::Accessor> _Accessors;
            VertexBufferObject _VertexBuffer;
            ElementBufferObject _ElementBuffer;
            VertexArrayObject _VertexArray;
            
            blehMath::mat4 _ModelMatrix;
    
    };


}
