#pragma once
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "../Events/Event.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

namespace REngine {
    class FPSCamera {
    public:
        FPSCamera(glm::vec3 position, glm::vec3 worldUp);
        ~FPSCamera();

        void LookAt();
        void OnUpdate();
        void OnEvent(Event& e);
        glm::mat4 GetViewMatrix();

        glm::vec3 GetPosition();
        glm::vec3 GetFront();
    private:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 worldUp;

        float yaw;
        float pitch;
        float movementSpeed = 1.0f;
        float sensitivity = 0.25f;
        float actualSpeed = 1.0f;

        void UpdateVectors();
        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnMouseMove(MouseMovedEvent& e);
    };
}
