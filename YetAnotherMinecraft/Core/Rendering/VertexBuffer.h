#pragma once
#include <cstdint>

namespace REngine {
    class VertexBuffer {
    private:
        uint32_t id;
        uint32_t size;
    public:
        VertexBuffer(const void* data, uint32_t size);
        VertexBuffer();
        ~VertexBuffer();

        void Bind() const;
        void UnBind() const;

        inline uint32_t GetSize() const { return size; }
    };
}