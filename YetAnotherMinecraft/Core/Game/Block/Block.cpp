#include "Block.h"

namespace REngine {
    float Block::vertices[] = {
        // [position 4] [normal 3] [texture coodinate 2] [face color 3] [atlas coord 2]
        // back face
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom-left
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// top-right
         1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom-right         
         1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// top-right
        -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// bottom-left
        -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// top-left
        // front face
        -1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// bottom-left
         1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// bottom-right
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// top-right
         1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// top-right
        -1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// top-left
        -1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// bottom-left
        // left face
        -1.0f,  1.0f,  1.0f,  2.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// top-right
        -1.0f,  1.0f, -1.0f,  2.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// top-left
        -1.0f, -1.0f, -1.0f,  2.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom-left
        -1.0f, -1.0f, -1.0f,  2.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom-left
        -1.0f, -1.0f,  1.0f,  2.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom-right
        -1.0f,  1.0f,  1.0f,  2.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// top-right
        // right face
         1.0f,  1.0f,  1.0f,  3.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// top-left
         1.0f, -1.0f, -1.0f,  3.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// bottom-right
         1.0f,  1.0f, -1.0f,  3.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// top-right         
         1.0f, -1.0f, -1.0f,  3.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// bottom-right
         1.0f,  1.0f,  1.0f,  3.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// top-left
         1.0f, -1.0f,  1.0f,  3.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,// bottom-left     
        // bottom face
        -1.0f, -1.0f, -1.0f,  4.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// top-right
         1.0f, -1.0f, -1.0f,  4.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// top-left
         1.0f, -1.0f,  1.0f,  4.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom-left
         1.0f, -1.0f,  1.0f,  4.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom-left
        -1.0f, -1.0f,  1.0f,  4.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom-right
        -1.0f, -1.0f, -1.0f,  4.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,// top-right
        // top face
        -1.0f,  1.0f, -1.0f,  5.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// top-left
         1.0f,  1.0f , 1.0f,  5.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// bottom-right
         1.0f,  1.0f, -1.0f,  5.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// top-right     
         1.0f,  1.0f,  1.0f,  5.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// bottom-right
        -1.0f,  1.0f, -1.0f,  5.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// top-left
        -1.0f,  1.0f,  1.0f,  5.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f,// bottom-left        
    };

    bool Block::isInitialized = false;

    std::unique_ptr<VertexBuffer> Block::vbo;
    std::unique_ptr<VertexBufferLayout> Block::layout;
    std::unique_ptr <VertexArray> Block::vao;

    Block::Block(): model(1.0f) {
    }
}