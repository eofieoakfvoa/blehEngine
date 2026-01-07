#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
    : _RendererID(0)
{
    glGenVertexArrays(1, &_RendererID);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &_RendererID);
}

void VertexArrayObject::Bind()
{
    glBindVertexArray(_RendererID); //kolla så den har ett värde
} 
