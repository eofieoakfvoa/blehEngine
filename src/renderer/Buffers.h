#pragma once
#include "glad\glad.h"
#include <Services/Assets/gltfinformation.h>
namespace bleh
{
    class VertexBufferObject
    {

        private:
            unsigned int _rendererID;

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
            unsigned int GetID();

    };

    class ElementBufferObject
    {

        private:
            unsigned int _rendererID;

        public:
            ElementBufferObject();
            ElementBufferObject(unsigned int* Indices, unsigned int Size);
            ~ElementBufferObject();
            ElementBufferObject(const ElementBufferObject&) = delete;
            ElementBufferObject& operator=(const ElementBufferObject&) = delete;
            void Bind();
            void Allocate(int buffersize);
            void Allocate(int buffersize, const void* Data);
            void AddData(char* buffer, int Offset, int Length);
            unsigned int GetID();

    };
}