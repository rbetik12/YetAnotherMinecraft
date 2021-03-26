#pragma once
#include <glm/mat4x4.hpp>
#include "../../Events/Event.h"
#include "../../Rendering/VertexArray.h"
#include "../../Log.h"
#include <glm/gtx/string_cast.hpp>

#define BACK_FACE_INDEX 0
#define FRONT_FACE_INDEX 1
#define LEFT_FACE_INDEX 2
#define RIGHT_FACE_INDEX 3
#define BOTTOM_FACE_INDEX 4
#define TOP_FACE_INDEX 5

namespace REngine {
    class Block {
    public:
        virtual void OnEvent(Event& e) = 0;
        virtual void OnUpdate() = 0;
        virtual uint32_t* GetTextureIds() = 0;
        virtual glm::vec2 GetFaceTextureCoords(uint32_t face) = 0;

        Block();

        inline glm::mat4& GetModel() {
            return model;
        }

        static VertexBuffer& GetVBO() {
            return *vbo.get();
        }

        static VertexArray& GetVAO() {
            return *vao.get();
        }

        static float* GetRawData() {
            return vertices;
        }

        static void Bind() {
            vbo->Bind();
            vao->Bind();
        }

        static void UnBind() {
            vbo->UnBind();
            vao->UnBind();
        }

        static void Init() {
            if (!isInitialized) {
                vbo.reset(new VertexBuffer(&vertices, sizeof(vertices)));
                layout.reset(new VertexBufferLayout());
                vao.reset(new VertexArray());

                layout->Push<float>(4);
                layout->Push<float>(3);
                layout->Push<float>(2);
                layout->Push<float>(3);
                vao->AddBuffer(*vbo.get(), *layout.get());
                isInitialized = true;
            }
            else {
                R_CORE_WARN("Block class was already initialized!");
            }
        }
    protected:
        glm::mat4 model;
    private:
        static float vertices[1152];
        static bool isInitialized;
        static std::unique_ptr<VertexBuffer> vbo;
        static std::unique_ptr<VertexBufferLayout> layout;
        static std::unique_ptr <VertexArray> vao;
    };
}
