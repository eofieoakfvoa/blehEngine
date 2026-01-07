#pragma once
#include "glad\glad.h"
#include <Services/gltfinformation.h>
class VertexBufferObject
{
private:
    unsigned int _rendererID;

public:
    VertexBufferObject();
    VertexBufferObject(float* vertices, unsigned int Size);
    ~VertexBufferObject();
    void Bind();
    void AddData(char* buffer, int offset, int length);
    void AllocateEmpty(int buffersize); //detta är probably jätte dummt idk men vill pröva, jag är rädd, borde nog garantera att den är empty innan också
};

class ElementBufferObject
{
private:
    unsigned int _rendererID;

public:
    ElementBufferObject();
    ElementBufferObject(unsigned int* Indices, unsigned int Size);
    ~ElementBufferObject();
    void Bind();
    void AllocateEmpty(int buffersize);
    void AddData(char* buffer, int Offset, int Length);
};