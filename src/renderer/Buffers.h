#pragma once
#include "glad\glad.h"

class VertexBufferObject
{
private:
    unsigned int _rendererID;

public:
    VertexBufferObject(float* vertices, unsigned int Size);
    ~VertexBufferObject();
};

class ElementBufferObject
{
private:
    unsigned int _rendererID;

public:
    ElementBufferObject(unsigned int* Indices, unsigned int Size);
    ~ElementBufferObject();
};