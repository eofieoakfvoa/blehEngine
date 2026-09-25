#include "Texture.h"
#include "stb_image.h"
namespace bleh
{
    Texture::Texture()
    {
        
    }
    Texture::~Texture()
    {

    }
    void Texture::SetActive(int Slot)
    {
        glBindTextureUnit(Slot, _RenderID);
    }
}
