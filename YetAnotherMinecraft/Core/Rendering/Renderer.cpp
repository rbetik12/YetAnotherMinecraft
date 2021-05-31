#include "Renderer.h"
#include <glad/glad.h>
namespace REngine {
    void Renderer::ConfigDepthTest(bool status) {
        if (status) {
            glEnable(GL_DEPTH_TEST);
        }
        else {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void Renderer::Clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(117.0f / 256.0f, 170.0f / 256.0f, 1.0f, 1.0f);
    }

    void Renderer::Clear(float r, float g, float b, float a, bool clearDepth) {
        if (clearDepth) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        else {
            glClear(GL_COLOR_BUFFER_BIT);
        }
        glClearColor(r, g, b, a);
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
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //glDisable(GL_CULL_FACE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void Renderer::DepthConfig(int command) {
        glDepthFunc(command);
    }
}