#include "FrameBuffer.h"
#include <glad/glad.h>
#include "../Log.h"
#include "stb_image_write.h"

namespace REngine {
    FrameBuffer::FrameBuffer(uint32_t width, uint32_t height, 
                             TextureColorPalette palette, FrameBufferType type) : id(0),
                                                                frameTextureId(0), width(width),
                                                                height(height),
                                                                renderBufferId(0), type(type),
                                                                palette(palette) {
        glGenFramebuffers(1, &id);
        Bind();
        glGenTextures(1, &frameTextureId);
        glBindTexture(GL_TEXTURE_2D, frameTextureId);

        switch (palette) {
        case TextureColorPalette::RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
            break;
        default:
            R_CORE_WARN("Unimplemented framebuffer texture type!");
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTextureId, 0);
        UnBind();
    }

    FrameBuffer::~FrameBuffer() {
        glDeleteFramebuffers(1, &id);
    }

    void FrameBuffer::SaveToFile(std::string path) {
        unsigned char* frameBufferRawData = nullptr;
        size_t bufferSize = 0;
        uint32_t componentsNumber = 0;
        Bind();
        switch (palette) {
        case TextureColorPalette::RGB:
            bufferSize = 3 * width * height;
            componentsNumber = 3;
            frameBufferRawData = new unsigned char[bufferSize];
            break;
        default:
            R_CORE_ERROR("Unimplemented palette!");
            break;
        }

        switch (palette) {
        case TextureColorPalette::RGB:
            glReadnPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, bufferSize, frameBufferRawData);
            break;
        default:
            R_CORE_ERROR("Unimplemented palette!");
            break;
        }
        UnBind();
        stbi_flip_vertically_on_write(1);
        stbi_write_png(path.c_str(), width, height, componentsNumber, frameBufferRawData, width * componentsNumber);
    }

    void FrameBuffer::AddDepthStencilBuffer() {
        Bind();
        glGenRenderbuffers(1, &renderBufferId);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBufferId);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferId);
        UnBind();
    }

    void FrameBuffer::Verify() {
        Bind();
        R_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Failed to complete framebuffer!");
        UnBind();
    }

    void FrameBuffer::Bind() const {
        switch (type) {
        case FrameBufferType::All:
            glBindFramebuffer(GL_FRAMEBUFFER, id);
            break;
        default:
            R_CORE_WARN("Unimplemented framebuffer type!");
            break;
        }
    }

    void FrameBuffer::UnBind() const {
        switch (type) {
        case FrameBufferType::All:
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            break;
        default:
            R_CORE_WARN("Unimplemented framebuffer type!");
            break;
        }
    }

    void FrameBuffer::BindTexture(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, frameTextureId);
    }

    void FrameBuffer::UnBindTexture() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}