#pragma once
#include "Chunk.h"
#include "../Block/Block.h"
#include "../Block/BlockIds.h"
#include "../../Rendering/Renderer.h"
#include "../../Utils/RVec.h"
#include <PerlinNoise.hpp>
#include "../../Application.h"

#define CHUNK_SIZE_X 32
#define CHUNK_SIZE_Y 32
#define CHUNK_SIZE_Z 32
#define CHUNK_SIZE CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z

namespace REngine {
    Chunk::Chunk(glm::vec3 position) {
        this->position = position;
        std::vector<CubeFace> cubeFaces;
        std::vector<CubeFace> transParentCubeFaces;
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
                        FillFace(cubeFaces, transParentCubeFaces, BACK_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x, y, z + 1) || IsEmptyBlock(x, y, z + 1, chunkBlocks)) {
                        FillFace(cubeFaces, transParentCubeFaces, FRONT_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x - 1, y, z) || IsEmptyBlock(x - 1, y, z, chunkBlocks)) {
                        FillFace(cubeFaces, transParentCubeFaces, LEFT_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x + 1, y, z) || IsEmptyBlock(x + 1, y, z, chunkBlocks)) {
                        FillFace(cubeFaces, transParentCubeFaces, RIGHT_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x, y - 1, z) || IsEmptyBlock(x, y - 1, z, chunkBlocks)) {
                        FillFace(cubeFaces, transParentCubeFaces, BOTTOM_FACE_INDEX, blockPos, blockType);
                    }
                    if (!WithinChunk(x, y + 1, z) || IsEmptyBlock(x, y + 1, z, chunkBlocks)) {
                        FillFace(cubeFaces, transParentCubeFaces, TOP_FACE_INDEX, blockPos, blockType);
                    }
                }
            }
        }

        //SortFaces(cubeFaces);
        SortFaces(transParentCubeFaces);
        vbo.reset(new VertexBuffer(cubeFaces.data(), sizeof(CubeFace) * cubeFaces.size()));
        transparentVbo.reset(new VertexBuffer(transParentCubeFaces.data(), sizeof(CubeFace) * transParentCubeFaces.size(), GL_DYNAMIC_DRAW));
        VertexBufferLayout layout;
        layout.Push<float>(4, true);
        layout.Push<float>(3);
        layout.Push<float>(2);
        layout.Push<float>(3);
        layout.Push<float>(2);
        vao.reset(new VertexArray());
        vao->AddBuffer(*vbo.get(), layout);
        transparentVao.reset(new VertexArray());
        transparentVao->AddBuffer(*transparentVbo.get(), layout);

        UpdateModelMatrix();
    }

    Chunk::~Chunk() {
        delete[] chunkBlocks;
    }

    void Chunk::Draw(const Shader& shader) {
        vbo->Bind();
        vao->Bind();
        Renderer::Draw(*vao.get(), *vbo.get(), shader);
        vbo->UnBind();
        vao->UnBind();
    }

    void Chunk::DrawTransparent(const Shader& shader) {
        transparentVbo->Bind();
        transparentVao->Bind();
        Renderer::Draw(*transparentVao.get(), *transparentVbo.get(), shader);
        transparentVbo->UnBind();
        transparentVao->UnBind();
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

    void Chunk::FillFace(std::vector<CubeFace>& cubeFaces, std::vector<CubeFace>& transparentCubeFaces, uint32_t faceId, RVec3& pos, BlockType type) {
        CubeFace face;
        Cube* cube = (Cube*)Block::GetRawData();
        uint32_t atlasCoordX = 0;
        uint32_t atlasCoordY = 0;
        bool isTransparent = false;

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
                isTransparent = true;
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
        if (isTransparent) {
            transparentCubeFaces.push_back(face);
        }
        else {
            cubeFaces.push_back(face);
        }
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

    void Chunk::SortFaces(std::vector<CubeFace>& cubeFaces) {
        std::sort(cubeFaces.begin(), cubeFaces.end(),
                  [](const CubeFace& face0, const CubeFace& face1) {
                      Application* application = Application::Get();
                      FPSCamera* camera = application->GetCamera();
                      glm::vec3 cameraPos = camera->GetPosition();
                      float dist0, dist1;
                      glm::vec3 v00, v01, v02, v10, v11, v12;

                      memcpy(&v00[0], &face0.vertexes[0].position, sizeof(float) * 3);
                      memcpy(&v01[0], &face0.vertexes[1].position, sizeof(float) * 3);
                      memcpy(&v02[0], &face0.vertexes[2].position, sizeof(float) * 3);

                      memcpy(&v10[0], &face1.vertexes[0].position, sizeof(float) * 3);
                      memcpy(&v11[0], &face1.vertexes[1].position, sizeof(float) * 3);
                      memcpy(&v12[0], &face1.vertexes[2].position, sizeof(float) * 3);

                      glm::vec3 n0 = glm::cross(v02 - v00, v01 - v00);
                      n0 = glm::normalize(n0);

                      glm::vec3 n1 = glm::cross(v12 - v10, v11 - v10);
                      n1 = glm::normalize(n1);

                      dist0 = std::fabs((n0.x * cameraPos.x + n0.y * cameraPos.y + n0.z * cameraPos.z) + (n0.x * v02.x + n0.y * v02.y + n0.z * v02.z)) / glm::length(n0);
                      dist1 = std::fabs((n1.x * cameraPos.x + n1.y * cameraPos.y + n1.z * cameraPos.z) + (n1.x * v12.x + n1.y * v12.y + n1.z * v12.z)) / glm::length(n1);
                      return dist0 > dist1;
                  }
        );
    }

    void Chunk::Move(glm::vec3 newCoords) {
        position = newCoords;
        UpdateModelMatrix();
    }

    void Chunk::Scale(glm::vec3 scaleVec) {
        scale = scaleVec;
        UpdateModelMatrix();
    }

    void Chunk::OnUpdate() {
        CubeFace* vboPtr = (CubeFace*)transparentVbo->Map(GL_READ_WRITE);
        std::vector<CubeFace> cubeFaces;

        cubeFaces.reserve(transparentVbo->GetSize() / sizeof(CubeFace));
        std::memcpy(cubeFaces.data(), vboPtr, transparentVbo->GetSize());

        SortFaces(cubeFaces);
        std::memcpy(vboPtr, cubeFaces.data(), transparentVbo->GetSize());
        transparentVbo->UnMap();
    }
}
