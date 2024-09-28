#include "glad.h"

class VertexBufferObject
{
    private:
        unsigned int _rendererID;
    public:
        VertexBufferObject(const void *Data, unsigned int Size);
        ~VertexBufferObject();
};

class IndexBufferObject
{
    private:
        unsigned int _rendererID;
    public:
        IndexBufferObject(const void *Data, unsigned int Size);
        ~IndexBufferObject();

};