#pragma once
#include "glad\glad.h"
namespace bleh
{
    class VertexArrayObject
    {
        public:
            VertexArrayObject();
            ~VertexArrayObject();
            //VertexArrayObject(const VertexArrayObject&) = delete;
            //VertexArrayObject& operator=(const VertexArrayObject&) = delete;
            void Generate();
            void Bind();
            unsigned int GetID();
        private:
            unsigned int _RendererID;

    };
}