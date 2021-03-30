#pragma once
#include <vector>
#include <memory>
#include "../../Rendering/VertexArray.h"
#include "../../Rendering/Shader.h"
#include "../../Utils/RVec.h"
#include "../Block/BlockIds.h"

namespace REngine {
    struct CubeFaceVertex {
        RVec4 position;
        RVec3 normal;
        RVec2 texCoord;
        RVec3 faceColor;
        RVec2 atlasCoord;
    };

    struct CubeFace {
        CubeFaceVertex vertexes[6];
    };

    struct Cube {
        CubeFace cubeFaces[6];
    };

    class Chunk {
    public:
        Chunk();

        void Draw(const Shader& shader);
        glm::mat4& GetModelMatrix();
    private:
        std::unique_ptr<VertexArray> vao;
        std::unique_ptr<VertexBuffer> vbo;
        glm::mat4 model;

        bool WithinChunk(uint32_t x, uint32_t y, uint32_t z);
        void FillFace(std::vector<CubeFace>& cubeFaces, uint32_t faceId, RVec3& pos, BlockType type);
    };
}
