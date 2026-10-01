#include "Buffers.h"
#include <print>
#include <cstdint>
namespace bleh
{
    VertexBufferObject::VertexBufferObject()
        : _RenderHandle(0)
    {
        glCreateBuffers(1, &_RenderHandle);
        std::println("Created VBO {}", _RenderHandle);
    }

    VertexBufferObject::VertexBufferObject(float* vertices, uint_fast32_t Size)
        : _RenderHandle(0)
    {
        glCreateBuffers(1, &_RenderHandle);
        glNamedBufferStorage(_RenderHandle, Size, vertices, 0);
    }

    VertexBufferObject::~VertexBufferObject()
    {
        glDeleteBuffers(1, &_RenderHandle);
    }

    void VertexBufferObject::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _RenderHandle);
    }

    void VertexBufferObject::AddData(char* buffer, int offset, int length)
    {
        glNamedBufferSubData(GL_ARRAY_BUFFER, offset, length, buffer);
    }

    void VertexBufferObject::Allocate(int buffersize)
    {
        glNamedBufferData(_RenderHandle, buffersize, NULL, GL_STATIC_DRAW);
    }


    void VertexBufferObject::Allocate(int buffersize, const void* data)
    {
        glNamedBufferData(_RenderHandle, buffersize, data, GL_STATIC_DRAW);
    }

    unsigned int VertexBufferObject::GetHandle()
    {
        return _RenderHandle;
    }









    ElementBufferObject::ElementBufferObject()
        : _RenderHandle(0)
    {
        glCreateBuffers(1, &_RenderHandle);
    }

    ElementBufferObject::ElementBufferObject(uint32_t* Indices, uint32_t Size)
        : _RenderHandle(0)
    {
        glCreateBuffers(1, &_RenderHandle);
        glNamedBufferStorage(_RenderHandle, Size, Indices, 0);
    }

    ElementBufferObject::~ElementBufferObject()
    {
        glDeleteBuffers(1, &_RenderHandle);
    }
    void ElementBufferObject::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _RenderHandle);
    }

    void ElementBufferObject::Allocate(int buffersize)
    {
        glNamedBufferData(_RenderHandle, buffersize, NULL, GL_STATIC_DRAW);
    }

    void ElementBufferObject::Allocate(int buffersize, const void* data)
    {
        glNamedBufferData(_RenderHandle, buffersize, data, GL_STATIC_DRAW);
    }

    void ElementBufferObject::AddData(char* buffer, int offset, int length)
    {
        glNamedBufferSubData(_RenderHandle, offset, length, buffer);
    }
    unsigned int ElementBufferObject::GetHandle()
    {
        return _RenderHandle;
    }





    FrameBufferObject::FrameBufferObject(FrameBufferSpecifications frame)
        :Specifications(frame)
    {
        std::println("creating framebuffer");
        glCreateFramebuffers(1, &_RenderHandle);
        
        glCreateTextures(GL_TEXTURE_2D, 1, &_ColorHandle);
        glTextureStorage2D(_ColorHandle, 1, GL_RGBA8, frame.Width, frame.Height);
        glTextureParameteri(_ColorHandle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(_ColorHandle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glNamedFramebufferTexture(_RenderHandle, GL_COLOR_ATTACHMENT0, _ColorHandle, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &_DepthHandle);
        glTextureStorage2D(_DepthHandle, 1, GL_DEPTH24_STENCIL8, frame.Width, frame.Height);

        glNamedFramebufferTexture(_RenderHandle, GL_DEPTH_STENCIL_ATTACHMENT, _DepthHandle, 0);

    }

    void FrameBufferObject::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, _RenderHandle);
    }

}
