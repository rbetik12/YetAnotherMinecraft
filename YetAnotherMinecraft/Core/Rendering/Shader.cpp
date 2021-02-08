#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Log.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

namespace REngine {
    Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        ShaderProgramSource source = ParseShaders(vertexShaderPath, fragmentShaderPath);
        id = CreateShader(source.vertexSource, source.fragmentSource);
    }

    Shader::~Shader() {
        glDeleteProgram(id);
    }

    void Shader::Bind() const {
        glUseProgram(id);
    }

    void Shader::UnBind() const {
        glUseProgram(0);
    }

    void Shader::SetUniform1ui(const std::string& name, uint32_t value) {
        glUniform1ui(GetUniformLocation(name), value);
    }

    void Shader::SetUniform1i(const std::string& name, int value) {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetUniform1f(const std::string& name, float value) {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }

    void Shader::SetUniform3f(const std::string& name, const glm::vec3& vec3) {
        glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
    }

    void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }

    void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix) {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix) {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
    }

    ShaderProgramSource Shader::ParseShaders(const std::string& vertexShaderPath, const std::string& fragmentShaderPath) {
        std::ifstream vertexShaderStream(vertexShaderPath);
        std::ifstream fragmentShaderStream(fragmentShaderPath);

        if (!vertexShaderStream.is_open()) {
            R_CORE_ERROR("Can't open vertex shader at path {0}", vertexShaderPath);
        }

        if (!fragmentShaderStream.is_open()) {
            R_CORE_ERROR("Can't open fragment shader at path {0}", fragmentShaderPath);
        }

        std::string line;
        std::stringstream ss[2];

        while (std::getline(vertexShaderStream, line)) {
            ss[0] << line << '\n';
        }

        while (std::getline(fragmentShaderStream, line)) {
            ss[1] << line << '\n';
        }

        return {ss[0].str(), ss[1].str()};
    }

    uint32_t Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
        uint32_t program = glCreateProgram();
        GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
        GLuint id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        GLint result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = new char[length];
            glGetShaderInfoLog(id, length, &length, message);
            std::string shaderType = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
            R_CORE_ERROR("Failed to compile {0} shader!", shaderType);
            R_CORE_ERROR("Error message: {0}", message);
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    int Shader::GetUniformLocation(const std::string& name) {
        if (uniformLocationCache.find(name) != uniformLocationCache.end())
            return uniformLocationCache[name];
        int location = glGetUniformLocation(id, name.c_str());
        if (location == -1)
            R_CORE_WARN("Uniform {0} doesn't exist!", name);
        uniformLocationCache[name] = location;
        return location;
    }
}