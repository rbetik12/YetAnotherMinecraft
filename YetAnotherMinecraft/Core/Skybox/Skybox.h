#pragma once
#include <memory>
#include <string>
#include "../Rendering/VertexBuffer.h"
#include "../Rendering/VertexArray.h"
#include "../Rendering/Shader.h"

namespace REngine {
    class Skybox {
    public:
        Skybox(std::string texturePath[6], std::string vertexShaderPath, std::string fragShaderPath);
        ~Skybox();

        void Bind(uint32_t slot = 0) const;
        void UnBind() const;
        Shader& GetShader();
        void Draw();
    private:
        static float skyboxVertices[108];

        uint32_t textureId;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<VertexBuffer> vbo;
        std::unique_ptr<VertexArray> vao;
    private:
        void LoadTexture(std::string texturePath[6]);
    };
}