#include "Core/Window/Window.h"
#include "Core/Log.h"
#include "Core/Application.h"


int main() {
    std::unique_ptr<REngine::Application> application(REngine::Application::Create());

    application->Run();
    return 0;
}
