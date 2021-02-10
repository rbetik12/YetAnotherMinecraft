#include "StoneBlock.h"
#include "../../Time.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace REngine {
    void StoneBlock::OnEvent(Event& e) {
    }

    void StoneBlock::OnUpdate() {
    }

    glm::vec2 StoneBlock::GetFaceTextureCoords(uint32_t face) {
        glm::vec2 vec = glm::vec2(textureIds[face * 2], textureIds[face * 2 + 1]);
        R_CORE_INFO("{0}", glm::to_string(vec));
        return vec;
    }
}