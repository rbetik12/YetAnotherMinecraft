#pragma once
#include <memory>
#include "Window/Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace REngine {
    class Application {
    public:
        static Application* Create();
        void Init();
        void Run();
        void OnEvent(Event &event);
    private:
        Application() {
            Init();
        }
        std::unique_ptr<Window> window;
        bool isRunning = false;
        bool OnWindowClose(WindowCloseEvent &e);
        bool OnMouseMove(MouseMovedEvent& e);
    };
}
