#include "Model.h"
#include <print>
namespace bleh
{ //idealy ändra hela mesh saken, borde bara vara information som renderern behöver
    using namespace bleh::gltf;
    Mesh::~Mesh()
    {
        std::println("mesh deleted");
    }
    void Mesh::print()
    {
        std::println("MESH DEBUG: start");    
        std::println("MESH DEBUG: BufferDataSize is {}", _Buffers[0].Data.size());

    }

    void Mesh::CreateVertexArray()
    {

        //borde probably inte ens ha detta i mesh klassen hahaha
        //tror jag först borde kolla igenom alla bufferviews och göra två listor en med vbo och en med ebo, sen där allocate
        _VertexBuffer.Bind(); // borde inte behövas eftersom AddData() gör det i dens kod dock ifall jag seperarar det från så kommer det här behövas
        //fixa dessa, du vet hur.
        _VertexBuffer.Allocate(_Buffers[0].Data.size(), _Buffers[0].Data.data()); //den här kör fortfarande hela buffern inclusive ebo
        _ElementBuffer.Allocate(_Buffers[0].Data.size(), _Buffers[0].Data.data());

        //_ElementBuffer.Allocate(_Accessors[_Primative.IndicesIndex].GetCount() * _Accessors[_Primative.IndicesIndex].GetComponentTypeInBytes(_Accessors[_Primative.IndicesIndex].GetComponentType()));


        for (auto& primative : meshParts)
        {
            primative.VertexArray.Generate();
            primative.VertexArray.Bind();
            _ElementBuffer.Bind();

            for (auto& [name, index] : primative.attributes)
            {
                if (index == -1) {
                    continue;
                }
                Accessor& accessor = _Accessors[index];

                BufferView& bufferview = _BufferViews[accessor.GetBufferView()];
                //Buffer& buffer = _Buffers[_BufferViews[accessor.GetBufferView()].GetBufferIndex()];

                //
                //_VertexBuffer.AddData(buffer.Data.data() + bufferview.GetByteOffset(), 
                //                      bufferview.GetByteOffset(), 
                //                      bufferview.GetByteLength()); //https://stackoverflow.com/questions/3872704/what-is-the-correct-way-to-offset-a-pointer
                _VertexBuffer.Bind();
                glEnableVertexAttribArray(static_cast<int>(name));
                glVertexAttribPointer(static_cast<int>(name),
                    accessor.GetVectorSize(accessor.GetType()),
                    accessor.GetComponentType(),
                    GL_FALSE,
                    bufferview.GetByteStride() != -1 ? bufferview.GetByteStride() : accessor.GetVectorSize(accessor.GetType()) * sizeof(float),
                    (void*)(intptr_t)(bufferview.GetByteOffset() + accessor.GetByteOffset())
                );

            }

            if (primative.IndicesIndex != -1)
            {
                Accessor& accessor = _Accessors[primative.IndicesIndex];
                BufferView& bufferview = _BufferViews[accessor.GetBufferView()];
                primative._IndexCount = accessor.GetCount();
                primative._IndexType = accessor.GetComponentType();
                //std::println("bufferviewByteOffset = {}, accessorByteOffset = {}", bufferview.GetByteOffset(), accessor.GetByteOffset());
                primative._IndicesByteOffset = bufferview.GetByteOffset() + accessor.GetByteOffset();
            }
        }

        glBindVertexArray(0);
        std::println("CREATING VERTEX ARRAY: end");
    }
}
