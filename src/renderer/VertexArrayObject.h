#pragma once
#include "Buffers.h"
class VertexArrayObject
{
    public:
        VertexArrayObject();
        ~VertexArrayObject();
        void Bind();
    private:
        unsigned int _RendererID;

};