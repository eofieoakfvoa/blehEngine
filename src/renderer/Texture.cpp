#include "Texture.h"
Texture::Texture(const std::string &filepath)
{
    glGenTextures(1, &_RenderID);
    glBindTexture(GL_TEXTURE_2D, _RenderID);
    unsigned char* data = stbi_load(filepath.c_str(), &Width, &Height, &nrChannels, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
Texture::~Texture()
{

}
void Texture::SetActive(GLenum textureLocation)
{
    glActiveTexture(textureLocation);
    glBindTexture(GL_TEXTURE_2D, _RenderID);
}
unsigned int Texture::GetRenderID()
{
    return _RenderID;
}