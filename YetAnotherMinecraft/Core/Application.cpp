#include "Application.h"
#include "Log.h"

namespace REngine {
    Application* Application::Create() {
        return new Application();
    }

    void Application::Init() {
        Log::init();
        window.reset(new Window(1920, 1080, "YetAnotherMinecraft"));
        window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        isRunning = true;
    }

    void Application::Run() {
        while (isRunning) {

            window->OnUpdate();
        }

        window->ShutDown();
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher e(event);
        e.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
    }
    bool Application::OnWindowClose(WindowCloseEvent& e) {
        isRunning = false;
        R_CORE_TRACE("Closing window!");
        return true;
    }
}
