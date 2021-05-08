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
        Chunk(glm::vec3 position);
        ~Chunk();

        void Draw(const Shader& shader);
        void DrawTransparent(const Shader& shader);
        glm::mat4& GetModelMatrix();
        virtual void Move(glm::vec3 newCoords) override;
        virtual void Scale(glm::vec3 scaleVec) override;
        virtual void OnUpdate() override;
    private:
        std::unique_ptr<VertexArray> vao;
        std::unique_ptr<VertexBuffer> vbo;
        std::unique_ptr<VertexArray> transparentVao;
        std::unique_ptr<VertexBuffer> transparentVbo;
        BlockType* chunkBlocks;
       
    private:
        bool WithinChunk(uint32_t x, uint32_t y, uint32_t z);
        bool IsEmptyBlock(uint32_t x, uint32_t y, uint32_t z, BlockType* chunkMap);
        void FillFace(std::vector<CubeFace>& cubeFaces, std::vector<CubeFace>& transparentCubeFaces, uint32_t faceId, RVec3& pos, BlockType type);
        BlockType* GenerateChunkBlocks();
        void GenerateTrees(BlockType* _chunkBlocks, uint32_t height, uint32_t x, uint32_t z);
        void SortFaces(std::vector<CubeFace>& cubeFaces);
    };
}
