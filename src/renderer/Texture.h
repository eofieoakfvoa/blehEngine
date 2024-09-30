#include "stb_image.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    void SetActive();
    unsigned int GetRenderID();

};