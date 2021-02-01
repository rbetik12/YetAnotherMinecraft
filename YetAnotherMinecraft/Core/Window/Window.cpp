#include <glad/glad.h>
#include "Window.h"
#include "../Core.h"
#include "../Events/ApplicationEvent.h"

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
}