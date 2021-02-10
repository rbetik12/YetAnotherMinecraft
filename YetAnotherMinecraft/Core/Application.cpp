#include "Debug/Debug.h"
#include "Application.h"
#include "Log.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"
#include "Rendering/VertexArray.h"
#include "Rendering/IndexBuffer.h"
#include "Time.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>
#include <imgui.h>
#include "Game/Block/StoneBlock.h"
#include "Rendering/Texture.h"

namespace REngine {
    Application* Application::Create() {
        instance = new Application();
        return instance;
    }

    Application* Application::Get() {
        R_CORE_ASSERT(instance, "Application instance is null!");
        return instance;
    }

    void Application::Init() {
        Log::init();
        
        window.reset(new Window(1920, 1080, "YetAnotherMinecraft"));
        window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
        Debug::Init();
        Block::Init();
        Renderer::Init();

        camera.reset(new FPSCamera(glm::vec3(1.0f, 1.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

        isRunning = true;
    }

    void Application::Run() {
        gui.reset(ImGuiUi::Create());

        Shader basicShader("resources/shaders/block.vert", "resources/shaders/block.frag");
        Texture blockAtlas("resources/textures/block-atlas.jpg");

        StoneBlock stoneBlock(glm::vec3(0));

        while (isRunning) {
            Time::OnUpdate();
            camera->OnUpdate();
            Renderer::Clear();

            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)window->GetWidth() / (GLfloat)window->GetHeight(), 0.1f, 100.0f);
            glm::mat4 view = camera->GetViewMatrix();

            stoneBlock.OnUpdate();
            basicShader.Bind();
            blockAtlas.Bind();
            basicShader.SetUniformMat4f("projection", projection);
            basicShader.SetUniformMat4f("view", view);
            basicShader.SetUniformMat4f("model", stoneBlock.GetModel());
            basicShader.SetUniform1i("blockTexture", 0);

            uint32_t textureCoordsCounter = 0;
            for (int i = 0; i < 6; i++) {
                basicShader.SetUniform2f("blockAtlasCoords[" + std::to_string(i) + "]", stoneBlock.GetFaceTextureCoords(i));
            }
            stoneBlock.Bind();
            Renderer::Draw(Block::GetVAO(), Block::GetVBO(), basicShader);

            gui->Begin();
            {
                ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
                ImGui::Begin("Debug");
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }
            gui->End();

            window->OnUpdate();
        }

        window->ShutDown();
    }

    void Application::OnEvent(Event& event) {
        EventDispatcher e(event);
        e.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        e.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(Application::OnKeyPressed));
        
        camera->OnEvent(event);
    }
    Window* Application::GetWindow() {
        return window.get();
    }
    bool Application::OnWindowClose(WindowCloseEvent& e) {
        isRunning = false;
        R_CORE_TRACE("Closing window!");
        return true;
    }

    bool Application::OnMouseMove(MouseMovedEvent& e) {
        return true;
    }

    bool Application::OnKeyPressed(KeyPressedEvent& e) {
        if (e.GetKeyCode() == GLFW_KEY_ESCAPE) {
            isRunning = false;
        }
        return true;
    }

    Application* Application::instance = nullptr;
}