#include <map>
#include <string>
#include <string_view>

#include <glm/glm.hpp>

namespace Renderer
{

    class ComputeShader
    {
    public:
        ComputeShader(std::string_view Path);
        ~ComputeShader();

        ComputeShader(const ComputeShader&) = delete;
        ComputeShader& operator=(const ComputeShader&) = delete;

        ComputeShader(ComputeShader&& other) noexcept;
        ComputeShader& operator=(ComputeShader&& other) noexcept;

        void bind() const;

        void dispatch(int x, int y, int z);

        unsigned int getHandle() const;

        // Uniform setters
        // Note: shader must be bound for it to work properly

        void SetBool(const std::string& name, bool value);
        void SetInt(const std::string& name, int value);
        void SetUInt(const std::string& name, unsigned int value);
        void SetFloat(const std::string& name, float value);

        void SetVec2(const std::string& name, const glm::vec2& value);
        void SetVec3(const std::string& name, const glm::vec3& value);
        void SetVec4(const std::string& name, const glm::vec4& value);
    
        void SetIVec2(const std::string& name, const glm::ivec2& value);
        void SetIVec3(const std::string& name, const glm::ivec3& value);
        void SetIVec4(const std::string& name, const glm::ivec4& value);

        void SetUVec2(const std::string& name, const glm::uvec2& value);
        void SetUVec3(const std::string& name, const glm::uvec3& value);
        void SetUVec4(const std::string& name, const glm::uvec4& value);

        void SetMat2(const std::string& name, const glm::mat2& value);
        void SetMat3(const std::string& name, const glm::mat3& value);
        void SetMat4(const std::string& name, const glm::mat4& value);


    private:
        int GetUniformLocation(const std::string& name);

        static std::string readFile(std::string_view path);
        static void checkLinkErrors(unsigned int program);

    private:
        unsigned int m_Handle;

        std::map<std::string, int> m_UniformLocationCache;
    };

}// Renderer
