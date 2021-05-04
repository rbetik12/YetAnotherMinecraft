#pragma once
#include <vector>
#include <memory>
#include "../../Rendering/VertexArray.h"
#include "../../Rendering/Shader.h"
#include "../../Utils/RVec.h"
#include "../Block/BlockIds.h"
#include "../GameObject/GameObject.h"

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

    class Chunk: public IGameObject {
    public:
        Chunk();

        void Draw(const Shader& shader);
        glm::mat4& GetModelMatrix();
        virtual void Move(glm::vec3 newCoords) override;
        virtual void Scale(glm::vec3 scaleVec) override;
    private:
        std::unique_ptr<VertexArray> vao;
        std::unique_ptr<VertexBuffer> vbo;

        bool WithinChunk(uint32_t x, uint32_t y, uint32_t z);
        bool IsEmptyBlock(uint32_t x, uint32_t y, uint32_t z, BlockType* chunkMap);
        void FillFace(std::vector<CubeFace>& cubeFaces, uint32_t faceId, RVec3& pos, BlockType type);
    };
}
