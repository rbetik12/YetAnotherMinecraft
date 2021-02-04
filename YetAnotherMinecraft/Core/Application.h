#pragma once
#include <memory>
#include "Window/Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "UI/ImGuiUI.h"

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
        bool isRunning = false;
        bool OnWindowClose(WindowCloseEvent &e);
        bool OnMouseMove(MouseMovedEvent& e);
        static Application* instance;
    };
}
