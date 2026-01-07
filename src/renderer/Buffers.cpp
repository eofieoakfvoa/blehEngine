#include "Buffers.h"

VertexBufferObject::VertexBufferObject()
    : _rendererID(0)
{
    glGenBuffers(1, &_rendererID);
}

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

void VertexBufferObject::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _rendererID);
}

void VertexBufferObject::AddData(char* buffer, int offset, int length)
{
    Bind();
    glBufferSubData(GL_ARRAY_BUFFER, offset, length, buffer);
}

void VertexBufferObject::AllocateEmpty(int buffersize)
{
    Bind();
    glBufferData(GL_ARRAY_BUFFER, buffersize, NULL, GL_STATIC_DRAW);
}









ElementBufferObject::ElementBufferObject()
    : _rendererID(0)
{
    glGenBuffers(1, &_rendererID);
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
void ElementBufferObject::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID);
}

void ElementBufferObject::AllocateEmpty(int buffersize)
{
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffersize, NULL, GL_STATIC_DRAW);
}

void ElementBufferObject::AddData(char* buffer, int offset, int length)
{
    Bind();
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, length, buffer);
}