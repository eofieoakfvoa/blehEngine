#include "VertexArrayObject.h"
VertexArrayObject::VertexArrayObject()
    : _RendererID(0)
{
    glGenVertexArrays(1, &_RendererID);
    glBindVertexArray(_RendererID);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &_RendererID);
}

