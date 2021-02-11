#pragma once
#include "Chunk.h"
#include "../Block/Block.h"
#include "../Block/BlockIds.h"
#include "../../Rendering/Renderer.h"
#include "../../Utils/RVec.h"

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

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16
#define CHUNK_SIZE CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z


namespace REngine {
    Chunk::Chunk(): model(1.0f) {
        Cube* cubes = new Cube[CHUNK_SIZE];
        Cube* basicCube = (Cube*) Block::GetRawData();

       //Holy shit I need to put this large loop in separate functions!
        uint32_t cubeID;
        for (uint32_t y = 0; y < CHUNK_SIZE_Y; y++) {
            for (uint32_t x = 0; x < CHUNK_SIZE_X; x++) {
                for (uint32_t z = 0; z < CHUNK_SIZE_Z; z++) {
                    cubeID = (y * CHUNK_SIZE_Z * CHUNK_SIZE_X) + (z * CHUNK_SIZE_X) + x;
                    std::memcpy(cubes + cubeID, basicCube, sizeof(Cube));
                    for (uint32_t cubeFaceID = 0; cubeFaceID < 6; cubeFaceID++) {
                        for (uint32_t cubeFaceVertexId = 0; cubeFaceVertexId < 6; cubeFaceVertexId++) {
                            RVec4& vertexPosition = cubes[cubeID].cubeFaces[cubeFaceID].vertexes[cubeFaceVertexId].position;
                            RVec2& vertexAtlasCoords = cubes[cubeID].cubeFaces[cubeFaceID].vertexes[cubeFaceVertexId].atlasCoord;
                            vertexPosition.y = vertexPosition.y + (y * 2);
                            vertexPosition.x = vertexPosition.x + (x * 2);
                            vertexPosition.z = vertexPosition.z + (z * 2);
                            if (y >= 8 && y <= 10) {
                                vertexAtlasCoords.x = BLOCK_IRON_ORE_X;
                                vertexAtlasCoords.y = BLOCK_IRON_ORE_Y;
                            }
                        }
                    }
                    if (cubes[cubeID].cubeFaces[0].vertexes[0].atlasCoord.x == BLOCK_IRON_ORE_X) {
                        R_CORE_INFO("IRON!");
                    }
                }
            }
        }

        vbo.reset(new VertexBuffer(cubes, sizeof(Cube) * CHUNK_SIZE));
        VertexBufferLayout layout;
        layout.Push<float>(4, true);
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(3);
        layout.Push<float>(2);
        vao.reset(new VertexArray());
        vao->AddBuffer(*vbo.get(), layout);

        model = glm::translate(model, glm::vec3(0.0f));
        model = glm::scale(model, glm::vec3(1.0f));
    }

    void Chunk::Draw(const Shader& shader) {
        vbo->Bind();
        vao->Bind();
        Renderer::Draw(*vao.get(), *vbo.get(), shader);
    }

    glm::mat4& Chunk::GetModelMatrix() {
        return model;
    }
}
