#include "FrameRenderer.h"
#include "Renderer.h"
#include "../Log.h"

namespace REngine {
    bool FrameRenderer::isInitialized = false;
    std::unique_ptr<VertexArray> FrameRenderer::vao;
    std::unique_ptr<VertexBuffer> FrameRenderer::vbo;

    float FrameRenderer::frameQuadVertices[24] = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    void FrameRenderer::Init() {
        if (!isInitialized) {
            vbo.reset(new VertexBuffer(&frameQuadVertices, sizeof(frameQuadVertices)));
            VertexBufferLayout layout;
            layout.Push<float>(2);
            layout.Push<float>(2);
            vao.reset(new VertexArray());
            vao->AddBuffer(*vbo.get(), layout);
            isInitialized = true;
        }
        else {
            R_CORE_WARN("Attempt to initialize already created frame renderer");
        }
    }

    void FrameRenderer::Draw(const Shader& shader) {
        vbo->Bind();
        vao->Bind();
        Renderer::Draw(*vao.get(), *vbo.get(), shader);
        vbo->UnBind();
        vao->UnBind();
    }

    void FrameRenderer::Delete() {}
}