#include "Time.h"
#include <GLFW/glfw3.h>

namespace REngine {
    void Time::OnUpdate() {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    float Time::lastFrame = 0.0f;
    float Time::deltaTime;
    float Time::currentFrame;
}