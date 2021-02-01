#pragma once
#include <cstdint>
#include <GLFW/glfw3.h>
#include <string>
#include "../Events/Event.h"

namespace REngine {
    class Window {
    public:
        Window(uint32_t width, uint32_t height, std::string windowName);

        bool IsShouldClose();
        void SwapBuffers();
        void ShutDown();
        void SetEventCallback(const std::function<void(Event&)>& func) {
            data.callback = func;
        }
        void OnUpdate();
    private:
        GLFWwindow* window = nullptr;
        uint32_t width;
        uint32_t height;
        using EventCallbackFn = std::function<void(Event&)>;

        struct WindowData {
            uint32_t width;
            uint32_t height;

            EventCallbackFn callback;
        };

        WindowData data;
    };
}