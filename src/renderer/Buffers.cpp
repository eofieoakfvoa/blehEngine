#include "Buffers.h"


VertexBufferObject::VertexBufferObject(float* vertices, unsigned int Size)
    : _rendererID(0)
{
    glGenBuffers(1, &_rendererID);
    glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
    glBufferData(GL_ARRAY_BUFFER, Size, vertices, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &_rendererID);
}





ElementBufferObject::ElementBufferObject(unsigned int* Indices, unsigned int Size)
    : _rendererID(0)
{
    glGenBuffers(1, &_rendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, Indices, GL_STATIC_DRAW);
}

ElementBufferObject::~ElementBufferObject()
{
    glDeleteBuffers(1, &_rendererID);
}