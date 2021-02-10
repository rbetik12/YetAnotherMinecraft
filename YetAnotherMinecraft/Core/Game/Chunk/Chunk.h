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
    private:
        std::unique_ptr<VertexArray> vao;
        std::unique_ptr<VertexBuffer> vbo;
    };
}
