#pragma once
#include <memory>
#include "Window/Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "UI/ImGuiUI.h"
#include "Camera/FPSCamera.h"
#include "Rendering/FrameBuffer.h"

namespace REngine {
    class Application {
    public:
        static Application* Create();
        static Application* Get();
        void Init();
        void Run();
        void OnEvent(Event &event);
        Window* GetWindow();
        FPSCamera* GetCamera();
    private:
        Application() {
            Init();
        }
        std::unique_ptr<Window> window;
        std::unique_ptr<ImGuiUi> gui;
        std::unique_ptr<FPSCamera> camera;
        std::unique_ptr<FrameBuffer> finalFrameBuffer;
        bool isRunning = false;
        bool OnWindowClose(WindowCloseEvent &e);
        bool OnMouseMove(MouseMovedEvent& e);
        bool OnKeyPressed(KeyPressedEvent& e);
        static Application* instance;
    };
}
