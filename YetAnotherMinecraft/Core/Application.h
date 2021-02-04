#pragma once
#include <memory>
#include "Window/Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "UI/ImGuiUI.h"
#include "Camera/FPSCamera.h"

namespace REngine {
    class Application {
    public:
        static Application* Create();
        static Application* Get();
        void Init();
        void Run();
        void OnEvent(Event &event);
        Window* GetWindow();
    private:
        Application() {
            Init();
        }
        std::unique_ptr<Window> window;
        std::unique_ptr<ImGuiUi> gui;
        std::unique_ptr<FPSCamera> camera;
        bool isRunning = false;
        bool OnWindowClose(WindowCloseEvent &e);
        bool OnMouseMove(MouseMovedEvent& e);
        bool OnKeyPressed(KeyPressedEvent& e);
        static Application* instance;
    };
}
