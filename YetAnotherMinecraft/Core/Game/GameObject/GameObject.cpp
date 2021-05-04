#include "GameObject.h"
#include <glm/ext/matrix_transform.hpp>

void REngine::IGameObject::UpdateModelMatrix() {
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
}
