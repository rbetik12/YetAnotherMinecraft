#pragma once
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

namespace REngine {
    class Renderer {
    public:
        static void Clear();
        static void Draw(const VertexArray& vao, const VertexBuffer& vbo, const Shader& shader);
        static void Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader);
        static void Init();
    };
}
