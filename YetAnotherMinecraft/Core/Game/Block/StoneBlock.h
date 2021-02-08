#pragma once
#include "Block.h"
#include <glm/gtx/transform.hpp>

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
    private:
        uint32_t textureIds[12] = { 0,1, 0,1, 0,1 ,0,1, 0,1, 0,1 };
    };
}
