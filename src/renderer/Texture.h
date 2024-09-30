#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#pragma once
class Texture
{
private:
    unsigned int _RenderID;
    int Width;
    int Height;
    int nrChannels;
public:
    Texture(const std::string &filepath);
    ~Texture();
    void SetActive(GLenum textureLocation);
    unsigned int GetRenderID();

};