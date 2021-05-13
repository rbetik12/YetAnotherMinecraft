#pragma once
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <mutex>

namespace REngine {
    class Renderer {
    public:
        static void Clear();
        static void Draw(const VertexArray& vao, const VertexBuffer& vbo, const Shader& shader);
        static void Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader);
        static void Init();
        static void DepthConfig(int command);
        static void Lock();
        static void Unlock();
    private:
        static std::mutex mutex;
    };
}
