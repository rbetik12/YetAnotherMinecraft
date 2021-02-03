#include "VertexBuffer.h"
#include <glad/glad.h>
#include "../Log.h"

namespace REngine {
    VertexBuffer::VertexBuffer(const void* data, uint32_t size): size(size) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        R_CORE_TRACE("Created vertex buffer with id {0}", id);
    }

    VertexBuffer::~VertexBuffer() {
    }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }
    void VertexBuffer::UnBind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}