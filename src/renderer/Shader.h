#include <string>
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
class Shader
{

private:

public:
    ShaderProgramSource ParseShader(const std::string &filepath);
    unsigned int CompileShader(const std::string &source, unsigned int type);
    unsigned int CreateShader(const std::string &vertexshader, const std::string &fragmentshader);

};