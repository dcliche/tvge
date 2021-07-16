#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace tvge {
class Window {
   public:
    Window(int w, int h, std::string name);
    ~Window();

    // Disable copy constructor
    Window(const Window&) = delete;

    // Disable copy operator
    Window& operator=(const Window&) = delete;

    bool shouldClose() { return glfwWindowShouldClose(m_window); }
    VkExtent2D extent() { return {static_cast<uint32_t>(m_width), static_cast<uint32_t>(m_height)}; }
    bool wasWindowResized() { return m_framebufferResized; }
    void resetWindowResizedFrag() { m_framebufferResized = false; }
    GLFWwindow* getGLFWwindow() const { return m_window; }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);

   private:
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    void initWindow();

    int m_width;
    int m_height;
    bool m_framebufferResized = false;

    std::string m_windowName;
    GLFWwindow* m_window;
};
}  // namespace tvge