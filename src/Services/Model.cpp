#include "Model.h"

void Mesh::Bind()
{
    _VertexArray.Bind();
}

void Mesh::CreateVertexArray()
{

    _VertexArray.Bind();
    _VertexBuffer.Bind(); // borde inte behövas eftersom AddData() gör det i dens kod dock ifall jag seperarar det från så kommer det här behövas
    _VertexBuffer.AllocateEmpty(_Buffers[0].Data.size());
    _ElementBuffer.Bind();
    _ElementBuffer.AllocateEmpty(72);


    int i = 0; // måste ju göra baserat på shader layout / men fixar senare
    for (Accessor& accessor : _Accessors)
    {

        BufferView& bufferview = _BufferViews[accessor.GetBufferView()];
        Buffer& buffer = _Buffers[_BufferViews[accessor.GetBufferView()].GetBufferIndex()];

        if (bufferview.GetTarget() == 34962) // gud jag måste fixa allt detta senare kl är 4 nu snälla bara låt mig göra klart detta 34962 är ARRAY_BUFFER
        {
            _VertexBuffer.AddData(buffer.Data.data() + bufferview.GetByteOffset(), bufferview.GetByteOffset(), bufferview.GetByteLength());
            _VertexBuffer.Bind();
            //måste fixa nästa line så den inte ger en varning lol
            glVertexAttribPointer(i, accessor.GetVectorSize(accessor.GetType()), accessor.GetComponentType(), GL_FALSE, accessor.GetVectorSize(accessor.GetType()) * sizeof(float), (void*) bufferview.GetByteOffset() + accessor.GetByteOffset());
            glEnableVertexAttribArray(i);
            i++;

        }
        else // borde vara element alltid
        {
            _ElementBuffer.AddData(buffer.Data.data() + bufferview.GetByteOffset(), 0, bufferview.GetByteLength());
            _IndexCount = accessor.GetCount();
            _IndexType = accessor.GetComponentType();

        }
    }
    //
}
