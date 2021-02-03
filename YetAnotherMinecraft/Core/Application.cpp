#include "Debug/Debug.h"
#include "Application.h"
#include "Log.h"
#include "Rendering/Renderer.h"
#include "Rendering/Shader.h"
#include "Rendering/VertexBuffer.h"
#include "Rendering/VertexBufferLayout.h"
#include "Rendering/VertexArray.h"
#include "Rendering/IndexBuffer.h"

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
        Debug::Init();
        Shader basicShader("resources/shaders/Basic.vert", "resources/shaders/Basic.frag");

        float quadVertices[] = {
            -1.f, -1.f, 0.0f,
            1.f, -1.f, 0.0f, 
            1.f, 1.f, 0.0f, 
            -1.f, 1.f, 0.0f,
        };

        uint32_t quadIndexes[] = {
            0, 1, 2,
            2, 3, 0
        };

        VertexBuffer quadVBO(&quadVertices, sizeof(quadVertices));
        VertexBufferLayout quadVBOLayout;
        quadVBOLayout.Push<float>(3);
        VertexArray quadVAO;
        quadVAO.AddBuffer(quadVBO, quadVBOLayout);
        IndexBuffer quadEBO(quadIndexes, sizeof(quadIndexes) / sizeof(uint32_t));

        while (isRunning) {
            Renderer::Clear();

            basicShader.Bind();
            quadVAO.Bind();
            quadEBO.Bind();
            Renderer::Draw(quadVAO, quadEBO, basicShader);


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

    bool Application::OnMouseMove(MouseMovedEvent& e) {
        R_CORE_TRACE("Mouse move. X: {0} Y: {1}", e.GetX(), e.GetY());
        return true;
    }
}