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

    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
        Bind();
        vb.Bind();
        const auto& elements = layout.GetElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++) {
            const auto& element = elements[i];
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
            offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
        }
    }
}