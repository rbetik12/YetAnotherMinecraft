#include "Light.h"

void REngine::Light::Move(glm::vec3 newCoords) {
    position = newCoords;
    UpdateModelMatrix();
}

void REngine::Light::Scale(glm::vec3 scaleVec) {}

void REngine::Light::OnUpdate() {}

glm::mat4& REngine::Light::GetModelMatrix() {
    return model;
}

void REngine::Light::SetDirection(glm::vec3& direction) {
    direction = direction;
}

void REngine::Light::SetAmbientColor(glm::vec3& color) {
    ambientColor = color;
}

void REngine::Light::SetDiffuseColor(glm::vec3& color) {
    diffuseColor = color;
}
