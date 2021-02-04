#include "FPSCamera.h"
#include <GLFW/glfw3.h>
#include "../Time.h"
#include "../Log.h"
#include "glm/gtx/string_cast.hpp"

namespace REngine {
    FPSCamera::FPSCamera(glm::vec3 position, glm::vec3 worldUp): position(position), worldUp(worldUp), yaw(-90.0f), pitch(0.0f) {
        UpdateVectors();
    }

    FPSCamera::~FPSCamera() {}

    void FPSCamera::LookAt() {}

    void FPSCamera::OnUpdate() {
        actualSpeed = movementSpeed * Time::deltaTime;
    }

    glm::mat4 FPSCamera::GetViewMatrix() {
        return glm::mat4();
    }

    glm::vec3 FPSCamera::GetPosition() {
        return glm::vec3();
    }

    glm::vec3 FPSCamera::GetFront() {
        return glm::vec3();
    }

    void FPSCamera::UpdateVectors() {
        glm::vec3 rotatedFront;
        rotatedFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        rotatedFront.y = sin(glm::radians(pitch));
        rotatedFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        front = glm::normalize(rotatedFront);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }

    void FPSCamera::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(FPSCamera::OnKeyPressed));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(FPSCamera::OnMouseMove));
    }

    bool FPSCamera::OnKeyPressed(KeyPressedEvent& e) {
        switch (e.GetKeyCode()) {
        case GLFW_KEY_W:
            position += actualSpeed;
            break;
        case GLFW_KEY_S:
            position -= actualSpeed;
            break;
        case GLFW_KEY_A:
            position -= glm::normalize(glm::cross(front, up)) * actualSpeed;
            break;
        case GLFW_KEY_D:
            position += glm::normalize(glm::cross(front, up)) * actualSpeed;
            break;
        }

        UpdateVectors();
        return true;
    }
    bool FPSCamera::OnMouseMove(MouseMovedEvent& e) {
        return true;
    }
}