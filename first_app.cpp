#include "first_app.hpp"

#include <array>
#include <chrono>
#include <stdexcept>

#include "camera.hpp"
#include "keyboard_movement_controller.hpp"
#include "simple_render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

namespace tvge {

FirstApp::FirstApp() { loadGameObjects(); }

FirstApp::~FirstApp() {}

void FirstApp::run() {
    SimpleRenderSystem simpleRenderSystem{m_device, m_renderer.getSwapChainRenderPass()};
    Camera camera{};

    auto viewerObject = GameObject::createGameObject();
    KeyboardMovementController cameraController{};

    auto currentTime = std::chrono::high_resolution_clock::now();

    while (!m_window.shouldClose()) {
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        cameraController.moveInPlaneXZ(m_window.getGLFWwindow(), frameTime, viewerObject);
        camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

        float aspect = m_renderer.getAspectRatio();
        camera.setPerspectiveProjection(glm::radians(50.0f), aspect, 0.1f, 10.0f);

        if (auto commandBuffer = m_renderer.beginFrame()) {
            m_renderer.beginSwapChainRenderPass(commandBuffer);
            simpleRenderSystem.renderGameObjects(commandBuffer, m_gameObjects, camera);
            m_renderer.endSwapChainRenderPass(commandBuffer);
            m_renderer.endFrame();
        }
    }

    vkDeviceWaitIdle(m_device.device());
}

void FirstApp::loadGameObjects() {
    std::shared_ptr<Model> model = Model::createModelFromFile(m_device, "models/smooth_vase.obj");
    auto gameObj = GameObject::createGameObject();
    gameObj.model = model;
    gameObj.transform.translation = {0.0f, 0.0f, 2.5f};
    gameObj.transform.scale = glm::vec3(3.0f);
    m_gameObjects.push_back(std::move(gameObj));
}

}  // namespace tvge