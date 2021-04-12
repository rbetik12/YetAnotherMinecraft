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

        void OnUpdate();
        void OnEvent(Event& e);
        glm::mat4 GetViewMatrix();

        glm::vec3& GetPosition();
        glm::vec3& GetRotation();
        glm::vec3 GetFront();
        float& GetCameraMovementSpeed();
        void ToggleMouseCapture();
        bool IsMouseCaptured();
    private:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 front;
        glm::vec3 right;
        glm::vec3 worldUp;
        glm::vec3 rotation;
        
        float movementSpeed = 50.0f;
        float sensitivity = 0.25f;
        float actualSpeed = 1.0f;
        float prevXMousePos = -1;
        float prevYMousePos = -1;

        bool captureMouse = true;

        void UpdateVectors();
        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnMouseMove(MouseMovedEvent& e);
    };
}
