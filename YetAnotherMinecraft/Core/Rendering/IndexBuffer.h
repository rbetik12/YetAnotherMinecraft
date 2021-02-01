#pragma once
#include <cstdint>

namespace REngine {
    class IndexBuffer {
    private:
        uint32_t id;
        uint32_t count;
    public:
        IndexBuffer(const uint32_t* data, uint32_t count);
        ~IndexBuffer();

        void Bind() const;
        void UnBind() const;

        inline unsigned int GetCount() const {
            return count;
        }
    };
}