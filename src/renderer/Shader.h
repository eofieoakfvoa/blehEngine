#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
class Shader
{

private:
    unsigned int _RendererID;
public:
    ShaderProgramSource ParseShader(const std::string &filepath);
    unsigned int CompileShader(const std::string &source, unsigned int type);
    unsigned int CreateShader(const std::string &vertexshader, const std::string &fragmentshader);
    void Use() ;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};