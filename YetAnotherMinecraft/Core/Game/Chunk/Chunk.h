#pragma once
#include <vector>
#include <memory>
#include "../../Rendering/VertexArray.h"
#include "../../Rendering/Shader.h"

namespace REngine {
    class Chunk {
    public:
        Chunk();

        void Draw(const Shader& shader);
        glm::mat4& GetModelMatrix();
    private:
        std::unique_ptr<VertexArray> vao;
        std::unique_ptr<VertexBuffer> vbo;
        glm::mat4 model;
    };
}
