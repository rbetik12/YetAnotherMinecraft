#pragma once
#include <vector>
#include <cassert>
#include <glad/glad.h>

namespace REngine {
    struct VertexBufferElement {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        static unsigned int GetSizeOfType(unsigned int type);
    };

    class VertexBufferLayout {
    private:
        std::vector<VertexBufferElement> elements;
        unsigned int stride;
    public:
        VertexBufferLayout() : stride(0) {

        }

        template<typename T>
        void Push(unsigned int count, bool normalized = false) {
            static_assert(true, "");
        }

        inline const std::vector<VertexBufferElement> GetElements() const& { return elements; }

        inline unsigned int GetStride() const { return stride; }
    };

    template<>
    inline void VertexBufferLayout::Push<float>(unsigned int count, bool normalized) {
        elements.push_back({ GL_FLOAT, count, (unsigned char)(normalized ? GL_TRUE : GL_FALSE) });
        stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<>
    inline void VertexBufferLayout::Push<unsigned int>(unsigned int count, bool normalized) {
        elements.push_back({ GL_UNSIGNED_INT, count, (unsigned char)(normalized ? GL_TRUE : GL_FALSE) });
        stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    inline void VertexBufferLayout::Push<unsigned char>(unsigned int count, bool normalized) {
        elements.push_back({ GL_UNSIGNED_BYTE, count, (unsigned char)(normalized ? GL_TRUE : GL_FALSE) });
        stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
}
