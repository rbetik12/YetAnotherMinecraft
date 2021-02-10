#pragma once
#include "Block.h"
#include <glm/gtx/transform.hpp>
#include "BlockIds.h"

namespace REngine {
    class StoneBlock : public Block {
    public:
        StoneBlock(glm::vec3 pos) {
            model = glm::translate(model, pos);
            model = glm::scale(model, glm::vec3(1.0f));
        }

        virtual uint32_t* GetTextureIds() override {
            return textureIds;
        }

        virtual void OnEvent(Event& e) override;

        virtual void OnUpdate() override;

        virtual glm::vec2 GetFaceTextureCoords(uint32_t face) override;
    private:
        uint32_t textureIds[BLOCK_FACES_ARRAY_SIZE] = { BLOCK_STONE, BLOCK_STONE, BLOCK_STONE, BLOCK_STONE, BLOCK_STONE, BLOCK_STONE };
    };
}
