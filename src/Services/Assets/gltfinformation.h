#pragma once
#include <vector>
#include <iostream>
#include <flat_map>
#include <unordered_map>
#include "renderer/VertexArrayObject.h"
#include <filesystem>
#include "Services/Assets/handle.h"
namespace bleh::gltf
{
     enum class ShaderLayout 
     {
         None = -1,
         Position,
         Normal,
         Tangent,
         TextCoord_0,
         TextCoord_1,
         TextCoord_2,
         TextCoord_3,
         TextCoord_4,
     };


    class Buffer
    {
        public:
        std::vector<char> Data;
    };
    class BufferView
    {
        public:
        BufferView(int buffer, int length,int offset,int stride,int target)
        {
            _BufferIndex = buffer;
            _ByteLength = length;
            _ByteOffset = offset;
            _ByteStride = stride;
            _Target = target;
        }


        inline int GetBufferIndex() const { return _BufferIndex; }
        inline int GetByteLength() const { return _ByteLength; }
        inline int GetByteOffset() const { return _ByteOffset; }
        inline int GetByteStride() const { return _ByteStride; }
        inline int GetTarget() const { return _Target; }



        private:
        int _BufferIndex = -1;
        int _ByteLength = -1;
        int _ByteOffset = -1;
        int _ByteStride = -1;
        int _Target = -1;
    };
    class Accessor
    {
        public:
        Accessor(int bufferview, int offset,int componenttype,int count, std::string type)
        {
            _BufferView = bufferview;
            _ByteOffset = offset;
            _ComponentType = componenttype;
            _Count = count;
            _Type = type;
        }

        inline int GetBufferView() const { return _BufferView; }
        inline int GetByteOffset() const { return _ByteOffset; }
        inline int GetComponentType() const { return _ComponentType; }
        inline int GetCount() const { return _Count; }
        inline std::string GetType() const { return _Type; }
    
        inline int GetVectorSize(std::string type) const {return _AccessorTypeLookUp.at(type); } 
    
        inline int GetComponentTypeInBytes(int type) const {return _AccessorComponentTypeLookUp.at(type); } 
        private:
        int _BufferView = -1;
        int _ByteOffset = -1;
        int _ComponentType = -1;
        int _Count = -1;
        std::string _Type;




        //borde inte vara här
        //må va suicide att göra att types är strings istället för enums men jag pallar inte spendera typ 30 sekunder, såg flat_map på youtube shorts och ville testa, vet inte ifall switch eller map eller unordered map är bättre är inte så smart 
        std::flat_map<std::string, int> _AccessorTypeLookUp = {{"SCALAR", 1}, {"VEC2", 2}, {"VEC3", 3}, {"VEC4", 4}, {"MAT2", 4}, {"MAT3", 9}, {"MAT4", 16}}; 
    
        //borde inte ha den här borde i model.cpp behöver man en accessor för att använda den även fast det alltid är samma
        std::flat_map<int, int> _AccessorComponentTypeLookUp = {{5120, 1},{5121,1},{5122,2},{5123,2},{5125,4},{5126,4}}; //https://registry.khronos.org/glTF/specs/2.0/glTF-2.0.html component type bytes istället för bits
    };

    class Primative
    {
        public:
            VertexArrayObject VertexArray;
            std::string Name;
            std::unordered_map<ShaderLayout, int> attributes;
        
            int IndicesIndex = -1;
            int Material = -1;
            int Mode = 4;

            int _IndexCount = -1;
            int _IndexType = -1;
            int _IndicesByteOffset = 0;
            
            //i riktiga mesh så ska den ha en handle till material tror jag
            blehHandle TextureHandle;
    };







    enum class alphaMode
    {
        OPAQUE,
        MASK,
        BLEND
    };
    class Image
    {
        public:
            std::filesystem::path URI; //filepath::path senare
    };
    class Sampler 
    {
        public:
            int magFilter;
            int minFilter;
            int wrapS;
            int wrapT;

    };
    class TextureGLTF
    {
        public: 
            int sampler;
            int source;
    };
    class TextureHandle
    {
        public:
            int Source;
    };
    class PBRMaterial
    {
        public:
            float BaseColorFactor[4];
            float MetallicFactor;
            float RoughnessFactor;
            int baseColorTexture;
            int metallicRoughnessTexture;

    };
    class Material
    {
        public:
            int normalTexture;
            int occlusion;
            int emissive;
            std::string Name;
            bool doubleSided;
            PBRMaterial PBR;
            float emissiveFactor[3];
            alphaMode alphaCoverage;
    };



}
