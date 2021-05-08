#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace REngine {
    class IGameObject {
    public:
        virtual void Move(glm::vec3 newCoords) = 0;
        virtual void Scale(glm::vec3 scaleVec) = 0;
        virtual void OnUpdate() = 0;
        virtual glm::mat4& GetModelMatrix() = 0;
    protected:
        IGameObject(): model(1), position(0), rotation(0), scale(1) {}

        virtual void UpdateModelMatrix();
    protected:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        glm::mat4 model;
    };
}