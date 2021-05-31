#include <memory>
#include "VertexArray.h"
#include "Shader.h"

namespace REngine {
    class FrameRenderer {
    public:
        static void Init();
        static void Delete();
        static void Draw(const Shader& shader);
    private:
        static bool isInitialized;
        static float frameQuadVertices[24];
        static std::unique_ptr<VertexArray> vao;
        static std::unique_ptr<VertexBuffer> vbo;
    };
}