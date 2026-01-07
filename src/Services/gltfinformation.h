#pragma once
#include <vector>
#include <iostream>
#include <flat_map>


class Buffer
{

    public:
    std::vector<char> Data;
};
class BufferView
{
    public:
    BufferView(int buffer, int length,int offset,int stride,int target)
    {
        _BufferIndex = buffer;
        _ByteLength = length;
        _ByteOffset = offset;
        _ByteStride = stride;
        _Target = target;
    }


    inline int GetBufferIndex() const { return _BufferIndex; }
    inline int GetByteLength() const { return _ByteLength; }
    inline int GetByteOffset() const { return _ByteOffset; }
    inline int GetByteStride() const { return _ByteStride; }
    inline int GetTarget() const { return _Target; }



    private:
    int _BufferIndex = -1;
    int _ByteLength = -1;
    int _ByteOffset = -1;
    int _ByteStride = -1;
    int _Target = -1;
};
class Accessor
{
    public:
    Accessor(int bufferview, int offset,int componenttype,int count, std::string type)
    {
        _BufferView = bufferview;
        _ByteOffset = offset;
        _ComponentType = componenttype;
        _Count = count;
        _Type = type;
    }

    inline int GetBufferView() const { return _BufferView; }
    inline int GetByteOffset() const { return _ByteOffset; }
    inline int GetComponentType() const { return _ComponentType; }
    inline int GetCount() const { return _Count; }
    inline std::string GetType() const { return _Type; }
    
    inline int GetVectorSize(std::string type) const {return _AccessorTypeLookUp.at(type); } 
    
    private:
    int _BufferView = -1;
    int _ByteOffset = -1;
    int _ComponentType = -1;
    int _Count = -1;
    std::string _Type;
    //må va suicide att göra att types är strings istället för enums men jag pallar inte spendera typ 30 sekunder, såg flat_map på youtube shorts och ville testa, vet inte ifall switch eller map eller unordered map är bättre är inte så smart 
    std::flat_map<std::string, int> _AccessorTypeLookUp = {{"SCALAR", 1}, {"VEC2", 2}, {"VEC3", 3}, {"VEC4", 4}, {"MAT2", 4}, {"MAT3", 9}, {"MAT4", 16}}; 
};
