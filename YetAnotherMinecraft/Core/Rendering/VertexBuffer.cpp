#include "VertexBuffer.h"
#include "../Log.h"

namespace REngine {
    VertexBuffer::VertexBuffer(const void* data, uint32_t size, int drawMode): size(size) {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        if (drawMode == GL_STATIC_DRAW) {
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        }
        else if (drawMode == GL_DYNAMIC_DRAW) {
            glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
        }

        R_CORE_TRACE("Created vertex buffer with id {0}", id);
    }

    VertexBuffer::VertexBuffer() {}

    VertexBuffer::~VertexBuffer() {
    }

    void VertexBuffer::Bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::UnBind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void* VertexBuffer::Map(int accessMode) const {
        void* buffPtr = nullptr;

        Bind();
        buffPtr = glMapBuffer(GL_ARRAY_BUFFER, accessMode);
        UnBind();
        return buffPtr;
    }

    void VertexBuffer::UnMap() const {
        Bind();
        glUnmapBuffer(GL_ARRAY_BUFFER);
        UnBind();
    }
}