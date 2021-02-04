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

    void FPSCamera::OnUpdate() {
        actualSpeed = movementSpeed * Time::deltaTime;
    }

    glm::mat4 FPSCamera::GetViewMatrix() {
        return glm::lookAt(position, position + front, up);
    }

    glm::vec3 FPSCamera::GetPosition() {
        return position;
    }

    glm::vec3 FPSCamera::GetFront() {
        return front;
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
            position += actualSpeed * front;
            break;
        case GLFW_KEY_S:
            position -= actualSpeed * front;
            break;
        case GLFW_KEY_A:
            position -= glm::normalize(glm::cross(front, up)) * actualSpeed;
            break;
        case GLFW_KEY_D:
            position += glm::normalize(glm::cross(front, up)) * actualSpeed;
            break;
        }

        return true;
    }
    bool FPSCamera::OnMouseMove(MouseMovedEvent& e) {
        if (prevXMousePos == -1) {
            prevXMousePos = e.GetX();
            prevYMousePos = e.GetY();
        }
        float xOffset = e.GetX() - prevXMousePos;
        float yOffset = prevYMousePos - e.GetY();
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;


        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        UpdateVectors();
        prevXMousePos = e.GetX();
        prevYMousePos = e.GetY();
        return true;
    }
}