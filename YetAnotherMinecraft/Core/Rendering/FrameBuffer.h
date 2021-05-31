#include <cstdint>
#include "OpenGLEnums.h"
#include <string>

namespace REngine {

    enum class FrameBufferType {
        Read,
        Draw,
        All
    };
    
    class FrameBuffer {
    public:
        FrameBuffer(uint32_t width, uint32_t height, TextureColorPalette palette, FrameBufferType type);
        ~FrameBuffer();
        
        void SaveToFile(std::string path);
        void AddDepthStencilBuffer();
        void Verify();
        void Bind() const;
        void UnBind() const;
        void BindTexture(uint32_t slot = 0) const;
        void UnBindTexture() const;
    private:
        uint32_t id;
        uint32_t frameTextureId;
        uint32_t height, width;
        uint32_t renderBufferId;
        FrameBufferType type;
        TextureColorPalette palette;
    };
}