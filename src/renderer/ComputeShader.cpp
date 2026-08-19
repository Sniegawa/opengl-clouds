#include "ComputeShader.hpp"

#include <fstream>
#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>

namespace Renderer
{

    unsigned int CompileCompute(GLenum type, const char* src, const char* typestr)
    {
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "ERROR::SHADER::" << typestr << "::COMPILATION_FAILED\n" << infoLog << "\n";
        }

        return shader;
    }

    ComputeShader::ComputeShader(std::string_view Path)
    {
        std::string Src = readFile(Path);

        const char* Code = Src.c_str();

        unsigned int Shader = CompileCompute(GL_COMPUTE_SHADER, Code, "COMPUTE");

        m_Handle = glCreateProgram();

        glAttachShader(m_Handle, Shader);

        glLinkProgram(m_Handle);

        checkLinkErrors(m_Handle);

        glDeleteShader(Shader);
    }

    std::string ComputeShader::readFile(std::string_view path)
    {
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        std::stringstream ss;
        try {
            file.open(std::string(path));
            ss << file.rdbuf();
        }
        catch(const std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_READ: " << path << "\n";
        }
        return ss.str();
    }

    void ComputeShader::checkLinkErrors(unsigned int program)
    {
        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cout<< "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog<< "\n";
        }
    }
    

    ComputeShader::~ComputeShader()
    {
        glDeleteShader(m_Handle);
    }

    void ComputeShader::bind() const
    {
        glUseProgram(m_Handle);
    }


    int ComputeShader::GetUniformLocation(const std::string& name)
    {
        // TODO: Test if it calls hash lookup 2 times 
        
        if(m_UniformLocationCache.contains(name))
            return m_UniformLocationCache[name];


        auto loc = glGetUniformLocation(m_Handle, name.c_str());
        m_UniformLocationCache[name] = loc;
        return loc;
    }

   void ComputeShader::SetBool(const std::string& name, bool value)
    {
        glUniform1i(
            GetUniformLocation(name),
            value ? 1 : 0
        );
    }

    void ComputeShader::SetInt(const std::string& name, int value)
    {
        glUniform1i(
            GetUniformLocation(name),
            value
        );
    }

    void ComputeShader::SetUInt(const std::string& name, unsigned int value)
    {
        glUniform1ui(
            GetUniformLocation(name),
            value
        );
    }

    void ComputeShader::SetFloat(const std::string& name, float value)
    {
        glUniform1f(
            GetUniformLocation(name),
            value
        );
    }


    void ComputeShader::SetVec2(const std::string& name, const glm::vec2& value)
    {
        glUniform2fv(
            GetUniformLocation(name),
            1,
            glm::value_ptr(value)
        );
    }

    void ComputeShader::SetVec3(const std::string& name, const glm::vec3& value)
    {
        glUniform3fv(
            GetUniformLocation(name),
            1,
            glm::value_ptr(value)
        );
    }

    void ComputeShader::SetVec4(const std::string& name, const glm::vec4& value)
    {
        glUniform4fv(
            GetUniformLocation(name),
            1,
            glm::value_ptr(value)
        );
    }


    void ComputeShader::SetIVec2(const std::string& name, const glm::ivec2& value)
    {
        glUniform2iv(
            GetUniformLocation(name),
            1,
            glm::value_ptr(value)
        );
    }

    void ComputeShader::SetIVec3(const std::string& name, const glm::ivec3& value)
    {
        glUniform3iv(
            GetUniformLocation(name),
            1,
            glm::value_ptr(value)
        );
    }

    void ComputeShader::SetIVec4(const std::string& name, const glm::ivec4& value)
    {
        glUniform4iv(
            GetUniformLocation(name),
            1,
            glm::value_ptr(value)
        );
    }


    void ComputeShader::SetUVec2(const std::string& name, const glm::uvec2& value)
    {
        glUniform2uiv(
            GetUniformLocation(name),
            1,
            glm::value_ptr(value)
        );
    }

    void ComputeShader::SetUVec3(const std::string& name, const glm::uvec3& value)
    {
        glUniform3uiv(
            GetUniformLocation(name),
            1,
            glm::value_ptr(value)
        );
    }

    void ComputeShader::SetUVec4(const std::string& name, const glm::uvec4& value)
    {
        glUniform4uiv(
            GetUniformLocation(name),
            1,
            glm::value_ptr(value)
        );
    }


    void ComputeShader::SetMat2(const std::string& name, const glm::mat2& value)
    {
        glUniformMatrix2fv(
            GetUniformLocation(name),
            1,
            GL_FALSE,
            glm::value_ptr(value)
        );
    }

    void ComputeShader::SetMat3(const std::string& name, const glm::mat3& value)
    {
        glUniformMatrix3fv(
            GetUniformLocation(name),
            1,
            GL_FALSE,
            glm::value_ptr(value)
        );
    }

    void ComputeShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        glUniformMatrix4fv(
            GetUniformLocation(name),
            1,
            GL_FALSE,
            glm::value_ptr(value)
        );
    }
}// Renderer
