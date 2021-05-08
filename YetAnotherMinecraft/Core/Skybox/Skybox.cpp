#include "Skybox.h"
#include <stb_image.h>
#include "../Log.h"
#include "../Rendering/Renderer.h"

namespace REngine {
    Skybox::Skybox(std::string texturePath[6], std::string vertexShaderPath, std::string fragShaderPath) {
        shader.reset(new Shader(vertexShaderPath, fragShaderPath));

        vbo.reset(new VertexBuffer(&skyboxVertices, sizeof(skyboxVertices)));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        vao.reset(new VertexArray());
        vao->AddBuffer(*vbo.get(), layout);

        LoadTexture(texturePath);
    }

    Skybox::~Skybox() {}

    void Skybox::Bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
    }

    void Skybox::UnBind() const {
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    Shader& Skybox::GetShader() {
        return *shader.get();
    }

    void Skybox::Draw() {
        vao->Bind();
        Renderer::Draw(*vao.get(), *vbo.get(), *shader.get());
        vao->UnBind();
        shader->UnBind();
    }

    void Skybox::LoadTexture(std::string texturePath[6]) {
        glGenTextures(1, &textureId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);

        int width, height, nrChannels;
        unsigned char* data;
        stbi_set_flip_vertically_on_load(1);
        for (GLuint i = 0; i < 6; i++) {
            data = stbi_load(texturePath[i].c_str(), &width, &height, &nrChannels, 0);
            GLenum format = GL_RGBA;
            if (nrChannels == 1)
                format = GL_RED;
            else if (nrChannels == 3)
                format = GL_RGB;
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data
            );

            if (data) {
                stbi_image_free(data);
                R_CORE_INFO("Loaded texture at path {0} successfully!", texturePath[i].c_str());
            }
            else {
                R_CORE_ERROR("Failed to load texture at path: {0}");
            }

        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        UnBind();
    }

    float Skybox::skyboxVertices[] = {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    }; 
}