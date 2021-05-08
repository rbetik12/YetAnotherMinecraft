#pragma once
#include <cstdint>
#include <glad/glad.h>

namespace REngine {
    class VertexBuffer {
    private:
        uint32_t id;
        uint32_t size;
    public:
        VertexBuffer(const void* data, uint32_t size, int drawMode = GL_STATIC_DRAW);
        VertexBuffer();
        ~VertexBuffer();

        void Bind() const;
        void UnBind() const;
        void* Map(int accessMode) const;
        void UnMap() const;

        inline uint32_t GetSize() const { return size; }
    };
}