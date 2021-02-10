#pragma once
#include "Chunk.h"
#include "../../Rendering/Renderer.h"
#include "../../Utils/RVec.h"

struct CubeFace {
    RVec4 position;
    RVec3 normal;
    RVec2 texCoord;
    RVec3 faceColor;
    RVec2 atlasCoord;
};

namespace REngine {
    Chunk::Chunk() {
        float vertices[] = {
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,// bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,// top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,// bottom-right         
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,// top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,// bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,// top-left

            -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,// bottom-left
             1.0f,  3.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,// top-right
             1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,// bottom-right         
             1.0f,  3.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,// top-right
            -1.0f, 1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f,// bottom-left
            -1.0f,  3.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,// top-left
        };

        vbo.reset(new VertexBuffer(&vertices, sizeof(vertices)));
        VertexBufferLayout layout;
        layout.Push<float>(4, true);
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(3);
        vao.reset(new VertexArray());
        vao->AddBuffer(*vbo.get(), layout);
    }

    void Chunk::Draw(const Shader& shader) {
        vbo->Bind();
        vao->Bind();
        Renderer::Draw(*vao.get(), *vbo.get(), shader);
    }
}
