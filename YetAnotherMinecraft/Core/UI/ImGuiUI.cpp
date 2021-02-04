#include "ImGuiUI.h"
#include "../Application.h"

#define IMGUI_IMPL_API

#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace REngine{
    ImGuiUi* ImGuiUi::Create() {
        if (!instance) {
            instance = new ImGuiUi();
        }
        return instance;
    }

    ImGuiUi::ImGuiUi() {
        Init();
    }

    void ImGuiUi::Init() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui::StyleColorsDark();
        Application* app = Application::Get();
        Window* window = app->GetWindow();
        ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    ImGuiUi::~ImGuiUi() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiUi::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
    }

    void ImGuiUi::Begin() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiUi::End() {
        ImGui::Render();
        int displayW, displayH;
        glfwGetFramebufferSize(Application::Get()->GetWindow()->GetWindow(), &displayW, &displayH);
        glViewport(0, 0, displayW, displayH);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    ImGuiUi* ImGuiUi::instance = nullptr;
}
