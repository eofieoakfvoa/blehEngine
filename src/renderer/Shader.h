#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
namespace bleh
{
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };
    class Shader
    {

    private:
        uint32_t _RendererID;
    public:
        ShaderProgramSource ParseShader(const std::filesystem::path& filepath);
        uint32_t CompileShader(const std::string& source, uint32_t type);
        uint32_t CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
        void Use() ;
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMat4(const std::string& name, const glm::mat4& mat) const;
    };
}