#include <glad/glad.h>
#include "Window.h"
#include "../Core.h"
#include "../Events/ApplicationEvent.h"
#include "../Events/KeyEvent.h"
#include "../Events/MouseEvent.h"

namespace REngine {
    Window::Window(uint32_t width, uint32_t height, std::string windowName) : width(width), height(height) {
        if (!glfwInit())
            R_CORE_ERROR("Can't initialize GLFW!");

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);

        if (!window) {
            R_CORE_ERROR("Can't create window with name: " + windowName);
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        if (!status) {
            R_CORE_ERROR("Can't load GLAD!");
        }

        R_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
        R_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
        R_CORE_INFO("OpenGL version: {0}", glGetString(GL_VERSION));

        glfwSwapInterval(1);

        R_CORE_INFO("Created new window!");

        data.width = width;
        data.height = height;
        glfwSetWindowUserPointer(window, &data);

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            WindowCloseEvent e;
            data.callback(e);
                                   });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(key, 0);
                data.callback(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(key);
                data.callback(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(key, 1);
                data.callback(event);
                break;
            }
            }
                           });

        glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            KeyTypedEvent event(keycode);
            data.callback(event);
                            });

        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(button);
                data.callback(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(button);
                data.callback(event);
                break;
            }
            }
                                   });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event(xOffset, yOffset);
            data.callback(event);
                              });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event(xPos, yPos);
            data.callback(event);
                                 });
    }

    bool Window::IsShouldClose() {
        return glfwWindowShouldClose(window);
    }
    void Window::SwapBuffers() {
        glfwSwapBuffers(window);
    }

    void Window::ShutDown() {
        glfwDestroyWindow(window);
    }

    void Window::OnUpdate() {
        glfwPollEvents();
        SwapBuffers();
    }

    GLFWwindow* Window::GetWindow() {
        return window;
    }

    uint32_t Window::GetWidth() {
        return width;
    }

    uint32_t Window::GetHeight() {
        return height;
    }
}