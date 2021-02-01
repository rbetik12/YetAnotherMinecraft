#include "VertexArray.h"
#include <glad/glad.h>

namespace REngine {
    VertexArray::VertexArray() {
        glGenVertexArrays(1, &id);
    }
    VertexArray::~VertexArray() {}
    void VertexArray::Bind() const {
        glBindVertexArray(id);
    }
    void VertexArray::UnBind() const {
        glBindVertexArray(0);
    }
    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {}
}