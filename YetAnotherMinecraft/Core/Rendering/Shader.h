#pragma once
#include <glm/glm.hpp>
#include <unordered_map>

namespace REngine {
    struct ShaderProgramSource {
        std::string vertexSource;
        std::string fragmentSource;
    };

    class Shader {
    private:
        std::string filePath;
        uint32_t id = 0;
        std::unordered_map<std::string, int> uniformLocationCache;
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();

        void Bind() const;
        void UnBind() const;

        // Set uniforms
        void SetUniform1i(const std::string& name, int value);
        void SetUniform1f(const std::string& name, float value);
        void SetUniform3f(const std::string& name, float v0, float v1, float v2);
        void SetUniform3f(const std::string& name, const glm::vec3& vec3);
        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
        void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
    private:
        ShaderProgramSource ParseShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
        uint32_t CompileShader(uint32_t type, const std::string& source);
        int GetUniformLocation(const std::string& name);
    };
}