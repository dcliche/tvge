#pragma once

#include <memory>
#include <vector>

#include "device.hpp"
#include "game_object.hpp"
#include "renderer.hpp"
#include "window.hpp"

namespace tvge {
class FirstApp {
   public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    FirstApp();
    ~FirstApp();

    FirstApp(const FirstApp&) = delete;
    FirstApp& operator=(const FirstApp&) = delete;

    void run();

   private:
    void loadGameObjects();

    Window m_window{WIDTH, HEIGHT, "Hello Vulkan!"};
    Device m_device{m_window};
    Renderer m_renderer{m_window, m_device};

    std::vector<GameObject> m_GameObjects;
};
}  // namespace tvge