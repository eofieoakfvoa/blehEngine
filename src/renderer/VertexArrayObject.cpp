#include "VertexArrayObject.h"
namespace bleh
{
    VertexArrayObject::VertexArrayObject()
        : _RendererID(0)
    {
    }

    VertexArrayObject::~VertexArrayObject()
    {
   
        glDeleteVertexArrays(1, &_RendererID);
    }

    void VertexArrayObject::Generate()
    {
            glGenVertexArrays(1, &_RendererID);

    }

    void VertexArrayObject::Bind()
    {
        glBindVertexArray(_RendererID); //kolla så den har ett värde
    }
    unsigned int VertexArrayObject::GetID()
    {
        return _RendererID;
    }

}
