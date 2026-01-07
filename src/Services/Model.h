#pragma once
#include <vector>
#include <iostream>
#include <Services/gltfinformation.h>
#include <renderer/Buffers.h>
#include <renderer\VertexArrayObject.h>
#include <blehMath/blehMath.h>
class Model 
{
private:
public:
Model();
~Model();
};
class Mesh
{
    public:
    inline Mesh() : _ModelMatrix(1.0) {}
    
    //~Mesh();
    
    inline const std::vector<Buffer>& GetBuffers() const { return _Buffers; }
    inline const std::vector<BufferView>& GetBufferViews() const { return _BufferViews; }
    inline const std::vector<Accessor>& GetAccessors() const { return _Accessors; }
    inline const blehMath::mat4& GetModelMatrix() const { return _ModelMatrix; }
    
    void AddBuffer(Buffer buffer){_Buffers.emplace_back(buffer); }
    void AddBufferView(BufferView bufferview){_BufferViews.emplace_back(bufferview); }
    void AddAccessor(Accessor accessor){_Accessors.emplace_back(accessor); }
    void Bind();
    void CreateVertexArray();

    inline int GetIndexCount() { return _IndexCount; }
    inline int GetIndexType() { return _IndexType; }
    private:

    std::vector<Buffer> _Buffers;
    std::vector<BufferView> _BufferViews;
    std::vector<Accessor> _Accessors;
    VertexBufferObject _VertexBuffer;
    ElementBufferObject _ElementBuffer;
    VertexArrayObject _VertexArray;
    
    blehMath::mat4 _ModelMatrix;
    
    //temp
    int _IndexCount;
    int _IndexType;


};


