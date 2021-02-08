#include "Renderer.h"
#include <glad/glad.h>
namespace REngine {
    void Renderer::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.1, 1);
    }

    void Renderer::Draw(const VertexArray& vao, const VertexBuffer& vbo, const Shader& shader) {
       glDrawArrays(GL_TRIANGLES, 0, vbo.GetSize());
    }

    void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ebo, const Shader& shader) {
        glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer::Init() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_MULTISAMPLE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}