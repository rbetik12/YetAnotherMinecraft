#pragma once
#include "../Events/Event.h"

namespace REngine {
    class ImGuiUi {
    public:
        static ImGuiUi* Create();
        ~ImGuiUi();

        void OnEvent(Event &e);
        void OnUpdate();
    private:
        ImGuiUi();
        void Init();
        static ImGuiUi* instance;
    };
}
