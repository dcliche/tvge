#pragma once

#include <string>
#include <vector>

#include "device.hpp"

namespace xeni {

struct PipelineConfigInfo {
    PipelineConfigInfo(const PipelineConfigInfo&) = delete;
    PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

    VkPipelineViewportStateCreateInfo viewportInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    std::vector<VkDynamicState> dynamicStateEnables;
    VkPipelineDynamicStateCreateInfo dynamicStateInfo;
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
};

class Pipeline {
   public:
    Pipeline(Device& device, const std::string& vertFilepath, const std::string& fragFilePath,
             const PipelineConfigInfo& configInfo);
    ~Pipeline();

    Pipeline(const Pipeline&) = delete;
    Pipeline& operator=(const Pipeline&) = delete;

    void bind(VkCommandBuffer commandBuffer);

    static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);

   private:
    static std::vector<char> readFile(const std::string& filepath);

    void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilePath,
                                const PipelineConfigInfo& configInfo);

    void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

    Device& m_device;
    VkPipeline m_graphicsPipeline;
    VkShaderModule m_vertShaderModule;
    VkShaderModule m_fragShaderModule;
};
}  // namespace xeni