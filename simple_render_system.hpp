#pragma once

#include <memory>
#include <vector>

#include "camera.hpp"
#include "device.hpp"
#include "game_object.hpp"
#include "pipeline.hpp"

namespace tvge {
class SimpleRenderSystem {
   public:
    SimpleRenderSystem(Device& device, VkRenderPass renderPass);
    ~SimpleRenderSystem();

    SimpleRenderSystem(const SimpleRenderSystem&) = delete;
    SimpleRenderSystem& operator=(const SimpleRenderSystem&) = delete;

    void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<GameObject>& GameObjects, const Camera& camera);

   private:
    void createPipelineLayout();
    void createPipeline(VkRenderPass renderPass);

    Device& m_device;

    std::unique_ptr<Pipeline> m_pipeline;
    VkPipelineLayout m_pipelineLayout;
};
}  // namespace tvge