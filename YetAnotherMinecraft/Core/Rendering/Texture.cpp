#include "Texture.h"
#include <stb_image.h>
#include <glad/glad.h>
#include "../Log.h"

namespace REngine {
    Texture::Texture(const std::string& path) : localBuffer(nullptr),
        height(0), width(0),
        componentAmount(0), id(0) {
        //stbi_set_flip_vertically_on_load(1);
        localBuffer = stbi_load(path.c_str(), &width, &height, &componentAmount, 0);
        if (localBuffer) {
            GLenum format = GL_RGBA;
            if (componentAmount == 1)
                format = GL_RED;
            else if (componentAmount == 3)
                format = GL_RGB;

            glGenTextures(1, &id);
            glBindTexture(GL_TEXTURE_2D, id);

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, localBuffer);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            UnBind();
            R_CORE_INFO("Load texture at path {0} successfully!", path);
        }
        else {
            R_CORE_ERROR("Failed to load texture at path: {0}");
        }
        stbi_image_free(localBuffer);
    }

    void Texture::Bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void Texture::UnBind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
