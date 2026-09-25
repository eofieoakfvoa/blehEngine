#pragma once

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include "Services/Assets/handle.h"
namespace bleh
{
    class Texture
    {
        public:
            Texture();
            ~Texture();
            void SetActive(int slot);

            blehHandle Handle;
    
            uint32_t _RenderID;
            int Width;
            int Height;
            int nrChannels;

    };
}