#pragma once
#include "glad\glad.h"
#include <Services/Assets/gltfinformation.h>
namespace bleh
{
    class VertexBufferObject
    {

        private:
            uint32_t _RenderHandle;

        public:
            VertexBufferObject();
            VertexBufferObject(float* vertices, unsigned int Size);
            ~VertexBufferObject();
            VertexBufferObject(const VertexBufferObject&) = delete;
            VertexBufferObject& operator=(const VertexBufferObject&) = delete;
            
            void Bind();
            void AddData(char* buffer, int offset, int length);
            void Allocate(int buffersize); //detta är probably jätte dummt idk men vill pröva, jag är rädd, borde nog garantera att den är empty innan också
            void Allocate(int buffersize, const void* Data);
            uint32_t GetHandle();

    };

    class ElementBufferObject
    {

        private:
            uint32_t _RenderHandle;

        public:
            ElementBufferObject();
            ElementBufferObject(uint32_t* Indices, uint32_t Size);
            ~ElementBufferObject();
            ElementBufferObject(const ElementBufferObject&) = delete;
            ElementBufferObject& operator=(const ElementBufferObject&) = delete;

            void Bind();
            void Allocate(int buffersize);
            void Allocate(int buffersize, const void* Data);
            void AddData(char* buffer, int Offset, int Length);
            uint32_t GetHandle();

    };





    class FrameBufferSpecifications
    {
        public:
            uint32_t Width;
            uint32_t Height;

    };

    class FrameBufferObject
    {
        public:
            FrameBufferObject(FrameBufferSpecifications);
            void Bind();
            FrameBufferSpecifications Specifications;
            inline uint32_t GetColorHandle() const { return _ColorHandle; }
        private:
            
            uint32_t _RenderHandle;
            uint32_t _DepthHandle;
            uint32_t _ColorHandle;
    };

}