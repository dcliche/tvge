#include "window.hpp"

#include <stdexcept>

namespace xeni {
Window::Window(int w, int h, std::string name) : m_width{w}, m_height{h}, m_windowName{name} { initWindow(); }

Window::~Window() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Window::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    m_window = glfwCreateWindow(m_width, m_height, m_windowName.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferResizeCallback);
}

void Window::createWindowSurface(VkInstance instance, VkSurfaceKHR* surface) {
    if (glfwCreateWindowSurface(instance, m_window, nullptr, surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface");
    }
}

void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto aeWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    aeWindow->m_framebufferResized = true;
    aeWindow->m_width = width;
    aeWindow->m_height = height;
}

}  // namespace xeni