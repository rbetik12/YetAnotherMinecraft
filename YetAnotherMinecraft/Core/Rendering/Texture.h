#pragma once
#include <cstdint>
#include <string>

namespace REngine {
    class Texture {
    public:
        explicit Texture(const std::string& path);

        void Bind(uint32_t slot = 0) const;

        void UnBind() const;

        inline int GetWidth() const { return width; }
        inline int GetHeight() const { return height; }
    private:
        unsigned char* localBuffer;
        int width, height, componentAmount;
        uint32_t id;
    };
}
