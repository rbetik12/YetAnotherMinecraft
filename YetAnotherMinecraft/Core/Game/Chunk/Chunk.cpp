#pragma once
#include "Chunk.h"
#include "../Block/Block.h"
#include "../Block/BlockIds.h"
#include "../../Rendering/Renderer.h"
#include "../../Utils/RVec.h"
#include <PerlinNoise.hpp>

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 32
#define CHUNK_SIZE CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z

namespace REngine {
    Chunk::Chunk(glm::vec3 position) {
        this->position = position;
        std::vector<CubeFace> cubeFaces;
        chunkBlocks = GenerateChunkBlocks();
        BlockType blockType = Cobblestone;
        uint32_t cubeID;
        RVec3 blockPos;

        for (uint32_t x = 0; x < CHUNK_SIZE_X; x++) {
            for (uint32_t z = 0; z < CHUNK_SIZE_Z; z++) {
                for (uint32_t y = 0; y < CHUNK_SIZE_Y; y++) {
                    cubeID = (y * CHUNK_SIZE_Z * CHUNK_SIZE_X) + (z * CHUNK_SIZE_X) + x;
                    if (chunkBlocks[cubeID] == Empty) continue;

                    blockPos.x = x;
                    blockPos.y = y;
                    blockPos.z = z;
                    blockType = chunkBlocks[cubeID];
                    if (!WithinChunk(x, y, z - 1) || IsEmptyBlock(x, y, z - 1, chunkBlocks)) {
                        FillFace(cubeFaces, BACK_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x, y, z + 1) || IsEmptyBlock(x, y, z + 1, chunkBlocks)) {
                        FillFace(cubeFaces, FRONT_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x - 1, y, z) || IsEmptyBlock(x - 1, y, z, chunkBlocks)) {
                        FillFace(cubeFaces, LEFT_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x + 1, y, z) || IsEmptyBlock(x + 1, y, z, chunkBlocks)) {
                        FillFace(cubeFaces, RIGHT_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x, y - 1, z) || IsEmptyBlock(x, y - 1, z, chunkBlocks)) {
                        FillFace(cubeFaces, BOTTOM_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x, y + 1, z) || IsEmptyBlock(x, y + 1, z, chunkBlocks)) {
                        FillFace(cubeFaces, TOP_FACE_INDEX, blockPos, blockType);
                    }
                }
            }
        }

        vbo.reset(new VertexBuffer(cubeFaces.data(), sizeof(CubeFace) * cubeFaces.size()));
        VertexBufferLayout layout;
        layout.Push<float>(4, true);
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(3);
        layout.Push<float>(2);
        vao.reset(new VertexArray());
        vao->AddBuffer(*vbo.get(), layout);

        UpdateModelMatrix();
    }

    Chunk::~Chunk() {
        delete[] chunkBlocks;
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
        return x >= 0 && x < CHUNK_SIZE_X&& y >= 0 && y < CHUNK_SIZE_Y&& z >= 0 && z < CHUNK_SIZE_Z;
    }

    bool Chunk::IsEmptyBlock(uint32_t x, uint32_t y, uint32_t z, BlockType* chunkMap) {
        uint32_t cubeID = (y * CHUNK_SIZE_Z * CHUNK_SIZE_X) + (z * CHUNK_SIZE_X) + x;
        if (chunkMap[cubeID] == Empty) return true;
        return false;
    }

    void Chunk::FillFace(std::vector<CubeFace>& cubeFaces, uint32_t faceId, RVec3& pos, BlockType type) {
        CubeFace face;
        Cube* cube = (Cube*)Block::GetRawData();
        uint32_t atlasCoordX = 0;
        uint32_t atlasCoordY = 0;

        std::memcpy(&face, &cube->cubeFaces[faceId], sizeof(CubeFace));
        for (uint8_t i = 0; i < 6; i++) {
            RVec4& vertexPos = face.vertexes[i].position;
            switch (type) {
            case Gravel:
                atlasCoordX = BLOCK_GRAVEL_X;
                atlasCoordY = BLOCK_GRAVEL_Y;
                break;
            case IronOre:
                atlasCoordX = BLOCK_IRON_ORE_X;
                atlasCoordY = BLOCK_IRON_ORE_Y;
                break;
            case Dirt:
                atlasCoordX = BLOCK_DIRT_X;
                atlasCoordY = BLOCK_DIRT_Y;
                break;
            case Cobblestone:
                atlasCoordX = BLOCK_COBBLESTONE_X;
                atlasCoordY = BLOCK_COBBLESTONE_Y;
                break;
            case TreeSide:
                atlasCoordX = BLOCK_TREE_SIDE_X;
                atlasCoordY = BLOCK_TREE_SIDE_Y;
                break;
            case Leaf:
                atlasCoordX = BLOCK_LEAF_X;
                atlasCoordY = BLOCK_LEAF_Y;
                break;
            default:
                break;
            }

            face.vertexes[i].atlasCoord.x = atlasCoordX;
            face.vertexes[i].atlasCoord.y = atlasCoordY;
            vertexPos.x += pos.x * 2;
            vertexPos.y += pos.y * 2;
            vertexPos.z += pos.z * 2;
        }
        cubeFaces.push_back(face);
    }

    BlockType* Chunk::GenerateChunkBlocks() {
        const siv::PerlinNoise perlin(2);
        BlockType blockType = Cobblestone;
        uint32_t height;
        uint32_t cubeID;
        BlockType* _chunkBlocks = new BlockType[CHUNK_SIZE];

        memset(_chunkBlocks, 0, sizeof(BlockType) * CHUNK_SIZE);

        for (uint32_t x = 0; x < CHUNK_SIZE_X; x++) {
            for (uint32_t z = 0; z < CHUNK_SIZE_Z; z++) {
                height = perlin.accumulatedOctaveNoise2D_0_1((float)(x + ((int)position.x / 2)) / CHUNK_SIZE_X, 
                                                             (float)(z + ((int)position.z / 2)) / CHUNK_SIZE_Z, 1) * CHUNK_SIZE_Y;

                for (uint32_t y = 0; y < height; y++) {
                    cubeID = (y * CHUNK_SIZE_Z * CHUNK_SIZE_X) + (z * CHUNK_SIZE_X) + x;
                    if (y >= CHUNK_SIZE_Y - CHUNK_SIZE_Y / 2 || y == height - 1) {
                        blockType = Dirt;
                    }
                    else {
                        blockType = Cobblestone;
                    }
                    _chunkBlocks[cubeID] = blockType;
                }

                GenerateTrees(_chunkBlocks, height, x, z);
            }
        }

        return _chunkBlocks;
    }

    void Chunk::GenerateTrees(BlockType* _chunkBlocks, uint32_t height, uint32_t x, uint32_t z) {
        bool generateTree = false;
        uint32_t treeHeight = 0;
        uint32_t cubeID;
        uint32_t leafXLeftOffset;
        uint32_t leafZLeftOffset;
        uint32_t leafRadius = 2;
        double prob = (double)rand() / RAND_MAX;

        if (prob < 0.005) {
            generateTree = true;
        }
        else {
            generateTree = false;
        }

        treeHeight = 0;
        for (uint32_t y = height; y < CHUNK_SIZE_Y; y++) {
            cubeID = (y * CHUNK_SIZE_Z * CHUNK_SIZE_X) + (z * CHUNK_SIZE_X) + x;
            if (generateTree && treeHeight < 4) {
                _chunkBlocks[cubeID] = TreeSide;
                treeHeight += 1;
            }
            else if (generateTree && treeHeight >= 4 && treeHeight <= 6) {
                if (x <= leafRadius) {
                    leafXLeftOffset = 0;
                }
                else {
                    leafXLeftOffset = x - 2;
                }

                if (z <= leafRadius) {
                    leafZLeftOffset = 0;
                }
                else {
                    leafZLeftOffset = z - 2;
                }

                for (uint32_t leafX = leafXLeftOffset; leafX <= x + 2; leafX++) {
                    for (uint32_t leafZ = leafZLeftOffset; leafZ <= z + 2; leafZ++) {
                        if (WithinChunk(leafX, y, leafZ)) {
                            cubeID = (y * CHUNK_SIZE_Z * CHUNK_SIZE_X) + (leafZ * CHUNK_SIZE_X) + leafX;
                            if (treeHeight >= 5) {
                                prob = (double)rand() / RAND_MAX;
                                if (prob > 0.5 && (leafZ == z + 2 || leafX == x + 2 || leafX == x - 2 || leafZ == z - 2)) {
                                    _chunkBlocks[cubeID] = Empty;
                                }
                                else {
                                    _chunkBlocks[cubeID] = Leaf;
                                }
                            }
                            else {
                                _chunkBlocks[cubeID] = Leaf;
                            }
                        }
                    }
                }

                treeHeight += 1;
            }
        }
    }

    void Chunk::Move(glm::vec3 newCoords) {
        position = newCoords;
        UpdateModelMatrix();
    }

    void Chunk::Scale(glm::vec3 scaleVec) {
        scale = scaleVec;
        UpdateModelMatrix();
    }
}
