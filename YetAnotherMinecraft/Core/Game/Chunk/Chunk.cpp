#pragma once
#include "Chunk.h"
#include "../Block/Block.h"
#include "../Block/BlockIds.h"
#include "../../Rendering/Renderer.h"
#include "../../Utils/RVec.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 16
#define CHUNK_SIZE_Z 16
#define CHUNK_SIZE CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z

namespace REngine {
    Chunk::Chunk(): model(1.0f) {
        /*Cube* cubes = new Cube[CHUNK_SIZE];
        Cube* basicCube = (Cube*) Block::GetRawData();*/

       //Holy shit I need to put this large loop in separate functions!
        /*uint32_t cubeID;
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
                }
            }
        }*/

        std::vector<CubeFace> cubeFaces;
        BlockType chunkBlocks[CHUNK_SIZE] = {Gravel};
        uint32_t cubeID;
        for (uint32_t y = 0; y < CHUNK_SIZE_Y; y++) {
            for (uint32_t x = 0; x < CHUNK_SIZE_X; x++) {
                for (uint32_t z = 0; z < CHUNK_SIZE_Z; z++) {
                    cubeID = (y * CHUNK_SIZE_Z * CHUNK_SIZE_X) + (z * CHUNK_SIZE_X) + x;
                    if (!WithinChunk(x, y, z - 1)) {
                        FillFace(cubeFaces, BACK_FACE_INDEX, x, y, z);
                    }
                    if (!WithinChunk(x, y, z + 1)) {
                        FillFace(cubeFaces, FRONT_FACE_INDEX, x, y, z);
                    }
                    if (!WithinChunk(x - 1, y, z)) {
                        FillFace(cubeFaces, LEFT_FACE_INDEX, x, y, z);
                    }
                    if (!WithinChunk(x + 1, y, z)) {
                        FillFace(cubeFaces, RIGHT_FACE_INDEX, x, y, z);
                    }
                    if (!WithinChunk(x, y - 1, z)) {
                        FillFace(cubeFaces, BOTTOM_FACE_INDEX, x, y, z);
                    }
                    if (!WithinChunk(x, y + 1, z)) {
                        FillFace(cubeFaces, TOP_FACE_INDEX, x, y, z);
                    }
                }
            }
        }

        R_CORE_INFO("{0}", cubeFaces.size());
        vbo.reset(new VertexBuffer(cubeFaces.data(), sizeof(CubeFace) * cubeFaces.size()));
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

    bool Chunk::WithinChunk(uint32_t x, uint32_t y, uint32_t z) {
        return x >= 0 && x < CHUNK_SIZE_X && y >= 0 && y < CHUNK_SIZE_Y && z >= 0 && z < CHUNK_SIZE_Z;
    }

    void Chunk::FillFace(std::vector<CubeFace>& cubeFaces, uint32_t faceId, uint32_t x, uint32_t y, uint32_t z) {
        CubeFace face;
        Cube* cube = (Cube*)Block::GetRawData();
        /*uint32_t atlasCoordX = 0;
        uint32_t atlasCoordY = 0;*/

        std::memcpy(&face, &cube->cubeFaces[faceId], sizeof(CubeFace));
        for (uint8_t i = 0; i < 6; i++) {
            RVec4& vertexPos = face.vertexes[i].position;
            /*switch (type) {
            case Gravel:
                atlasCoordX = BLOCK_GRAVEL_X;
                atlasCoordY = BLOCK_GRAVEL_Y;
                break;
            default:
                break;
            }
            face.vertexes[i].atlasCoord.x = atlasCoordX;
            face.vertexes[i].atlasCoord.y = atlasCoordY;*/
            vertexPos.x += x * 2;
            vertexPos.y += y * 2;
            vertexPos.z += z * 2;
        }
        cubeFaces.push_back(face);
    }
}
