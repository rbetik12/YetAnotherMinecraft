#include "IndexBuffer.h"
#include <glad/glad.h>
#include "../Log.h"

namespace REngine {
    IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);

        R_CORE_TRACE("Created index buffer with id: {0}", id);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &id);
        R_CORE_TRACE("Deleted index buffer with id: {0}", id);
    }

    void IndexBuffer::Bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::UnBind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}