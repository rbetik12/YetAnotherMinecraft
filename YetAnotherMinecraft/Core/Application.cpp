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
#include "Game/Chunk/Chunk.h"
#include "Utils/RFloat.h"
#include "Skybox/Skybox.h"
#include <execution>
#include "Game/Light/Light.h"
#include "Rendering/FrameRenderer.h"

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

        camera.reset(new FPSCamera(glm::vec3(1.0f, 33.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

        isRunning = true;
    }

    void Application::Run() {
        gui.reset(ImGuiUi::Create());

        const int chunksAmount = 4;
        Shader basicShader("resources/shaders/chunk.vert", "resources/shaders/chunk.frag");
        Texture blockAtlas("resources/textures/block-atlas.png");

        std::array<Chunk*, chunksAmount> chunks = {
            new Chunk(glm::vec3(0, 0, 0)),
            new Chunk(glm::vec3(64, 0, 0)),
            new Chunk(glm::vec3(0, 0, 64)),
            new Chunk(glm::vec3(64, 0, 64)),
        };

        std::string cubemapFaces[] = {
            "resources/textures/cubemap/right.png",
            "resources/textures/cubemap/left.png",

            "resources/textures/cubemap/bottom.png",
            "resources/textures/cubemap/top.png",

            "resources/textures/cubemap/front.png",
            "resources/textures/cubemap/back.png"
        };

        Skybox skybox(cubemapFaces, "resources/shaders/skybox.vert", "resources/shaders/skybox.frag");

        uint32_t currentChunkIndex = 0;

        Light light;

        finalFrameBuffer.reset(new FrameBuffer(window->GetWidth(), window->GetHeight(), TextureColorPalette::RGB, FrameBufferType::All));
        finalFrameBuffer->AddDepthStencilBuffer();
        finalFrameBuffer->Verify();

        Shader screenShader("resources/shaders/framebuffer.vert", "resources/shaders/framebuffer.frag");
        FrameRenderer::Init();

        while (isRunning) {
            Time::OnUpdate();
            camera->OnUpdate();
            finalFrameBuffer->Bind();
            Renderer::ConfigDepthTest(true);
            Renderer::Clear();

            glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)window->GetWidth() / (GLfloat)window->GetHeight(), 0.1f, 300.0f);
            glm::mat4 view = camera->GetViewMatrix();

            basicShader.Bind();
            blockAtlas.Bind();
            basicShader.SetUniformMat4f("projection", projection);
            basicShader.SetUniformMat4f("view", view);
            basicShader.SetUniform1i("blockTexture", 0);
            basicShader.SetUniform3f("viewPos", camera->GetPosition().x, 
                                                camera->GetPosition().y,
                                                camera->GetPosition().z);
            basicShader.SetUniform3f("directionalLight.direction", light.GetDirection().x,
                                                                   light.GetDirection().y,
                                                                   light.GetDirection().z);
            basicShader.SetUniform3f("directionalLight.ambient", light.GetAmbientColor().x,
                                                                 light.GetAmbientColor().y,
                                                                 light.GetAmbientColor().z);
            basicShader.SetUniform3f("directionalLight.diffuse", light.GetDiffuseColor().x,
                                                                 light.GetDiffuseColor().y,
                                                                 light.GetDiffuseColor().z);
            basicShader.SetUniform3f("directionalLight.specular", 1.0f, 1.0f, 1.0f);
            std::sort(chunks.begin(), chunks.end(),
                      [](Chunk* chunk0, Chunk* chunk1) {
                          Application* application = Application::Get();
                          FPSCamera* camera = application->GetCamera();
                          glm::vec3 cameraPos = camera->GetPosition();
                          
                          float dist0, dist1;
                          dist0 = std::fabs(cameraPos.x - chunk0->GetPosition().x) + std::fabs(cameraPos.y - chunk0->GetPosition().y) + std::fabs(cameraPos.z - chunk0->GetPosition().z);
                          dist1 = std::fabs(cameraPos.x - chunk1->GetPosition().x) + std::fabs(cameraPos.y - chunk1->GetPosition().y) + std::fabs(cameraPos.z - chunk1->GetPosition().z);

                          return dist0 > dist1;
                      }
            );

            for (int i = chunksAmount - 1; i >= 0; i--) {
                basicShader.SetUniformMat4f("model", chunks[i]->GetModelMatrix());
                chunks[i]->Draw(basicShader);
            }

            Renderer::DepthConfig(GL_LEQUAL);
            skybox.GetShader().Bind();
            view = glm::mat4(glm::mat3(camera->GetViewMatrix()));
            skybox.GetShader().SetUniformMat4f("view", view);
            skybox.GetShader().SetUniformMat4f("projection", projection);
            skybox.Bind();
            skybox.Draw();
            skybox.UnBind();
            Renderer::DepthConfig(GL_LEQUAL);

            view = camera->GetViewMatrix();
            basicShader.Bind();
            blockAtlas.Bind();
            basicShader.SetUniformMat4f("projection", projection);
            basicShader.SetUniformMat4f("view", view);
            basicShader.SetUniform1i("blockTexture", 0);

            for (int i = chunksAmount - 1; i >= 0; i--) {
                if (chunks[i]->IsPlayerWithinChunk(camera->GetPosition())) {
                    currentChunkIndex = i;
                    chunks[i]->OnUpdate();
                }
                basicShader.SetUniformMat4f("model", chunks[i]->GetModelMatrix());
                chunks[i]->DrawTransparent(basicShader);
            }

            gui->Begin();
            {
                glm::vec3 prevRotation(0.0f);
                glm::vec3 currentChunkPos(0.0f);
                prevRotation[0] = camera->GetRotation()[0];
                prevRotation[1] = camera->GetRotation()[1];

                currentChunkPos = chunks[currentChunkIndex]->GetPosition();

                ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
                ImGui::Begin("Debug");
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::InputFloat3("Camera position", &camera->GetPosition()[0]);
                ImGui::InputFloat3("Camera rotation", &camera->GetRotation()[0]);
                ImGui::SliderFloat("Movement speed", &camera->GetCameraMovementSpeed(), 50.0f, 100.0f);
                ImGui::Text("Current chunk origin position: (%.1f, %.1f, %.1f)", currentChunkPos.x, currentChunkPos.y, currentChunkPos.z);
                if (!camera->IsMouseCaptured()) {
                    ImGui::Text("Toggled UI mode");
                    if (!FLOAT_EQ(prevRotation[0], camera->GetRotation()[0]) || !FLOAT_EQ(prevRotation[1], camera->GetRotation()[1])) {
                        // We trigger this event here, because we need to trigger recalculating of camera vectors.
                        MouseMovedEvent e(0.0f, 0.0f);
                        camera->OnEvent(e);
                    }
                }
                ImGui::End();

                ImGui::Begin("Directional light");
                ImGui::InputFloat3("Ambient color", &light.GetAmbientColor()[0]);
                ImGui::InputFloat3("Diffuse color", &light.GetDiffuseColor()[0]);
                ImGui::InputFloat3("Direction", &light.GetDirection()[0]);
                ImGui::End();
            }
            gui->End();

            finalFrameBuffer->UnBind();

            Renderer::ConfigDepthTest(false);
            Renderer::Clear(1.0f, 1.0f, 1.0f, 1.0f, false);
            finalFrameBuffer->BindTexture();
            screenShader.Bind();
            screenShader.SetUniform1i("screenTexture", 0);
            FrameRenderer::Draw(screenShader);
            finalFrameBuffer->UnBindTexture();
            window->OnUpdate();
        }
        for (auto chunk : chunks) {
            delete chunk;
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
    FPSCamera* Application::GetCamera() {
        return camera.get();
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
        else if (e.GetKeyCode() == GLFW_KEY_M) {
            camera->ToggleMouseCapture();
        }
        return true;
    }

    Application* Application::instance = nullptr;
}