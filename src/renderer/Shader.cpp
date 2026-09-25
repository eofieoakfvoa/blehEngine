#include "Shader.h"
#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
namespace bleh
{

    ShaderProgramSource Shader::ParseShader(const std::filesystem::path& filepath)
    {
        std::ifstream stream(filepath);

        if (!stream.is_open()) 
        {
            std::cerr << "Could not open shader file: " << filepath << std::endl;
            return {"", ""};
        }

        enum class ShaderType
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        ShaderType type = ShaderType::NONE;
        std::string line;
        std::stringstream ss[2];
        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else
            {
                ss[(int)type] << line << '\n';
            }
        }
        return {ss[0].str(), ss[1].str()};
    }

    uint32_t Shader::CompileShader(const std::string& source, uint32_t type)
    {
        uint32_t id = glCreateShader(type);
        _RendererID = id;
        const char *src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result); 
        if (result == GL_FALSE) 
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> message(length);
            glGetShaderInfoLog(id, length, &length, message.data());
            std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
            std::cout << "Shader source:\n" << source << std::endl;
            std::cout << message.data() << std::endl;
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    uint32_t Shader::CreateShader(const std::string& vertexshader, const std::string& fragmentshader)
    {
        uint32_t program = glCreateProgram();
        uint32_t vs = CompileShader(vertexshader, GL_VERTEX_SHADER);

        uint32_t fs = CompileShader(fragmentshader, GL_FRAGMENT_SHADER);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);

        int result;
        glGetProgramiv(program, GL_LINK_STATUS, &result); 
        if (result == GL_FALSE) 
        {
            int length;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
            std::vector<char> message(length);
            glGetProgramInfoLog(program, length, &length, message.data());
            std::cout << "Failed to link shader program!" << std::endl;
            std::cout << message.data() << std::endl;
            glDeleteProgram(program);
            return 0;
        }



        //försvinner inte  https://gamedev.stackexchange.com/questions/47910/after-a-succesful-gllinkprogram-should-i-delete-detach-my-shaders
        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }
    void Shader::Use() 
    { 
        glUseProgram(_RendererID);
    }  
    void Shader::setBool(const std::string& name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(_RendererID, name.c_str()), (int)value); 
    }
    void Shader::setInt(const std::string& name, int value) const
    { 
        glUniform1i(glGetUniformLocation(_RendererID, name.c_str()), value); 
    }
    void Shader::setFloat(const std::string& name, float value) const
    { 
        glUniform1f(glGetUniformLocation(_RendererID, name.c_str()), value); 
    }
    void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
}