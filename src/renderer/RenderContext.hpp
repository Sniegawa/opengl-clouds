#pragma once

#include <glm/glm.hpp>
#include "UniformBuffer.hpp"

namespace Renderer
{
    struct CameraData
    {
        glm::mat4 View = glm::mat4(1.0f);
        glm::mat4 Projection = glm::mat4(1.0f);
        glm::mat4 InverseViewProjection = glm::mat4(1.0f);
        glm::vec3 Position = glm::vec3(0.0f);
        float pad1 = 0.0f;
    };

    struct FrameData
    {
        glm::vec2 resolution = glm::vec2(800,600);
        float time = 0.0f;
        float pad1 = 0.0f;
    };

    
    class RenderContext
    {
        public:
            RenderContext();
            ~RenderContext();

            RenderContext(const RenderContext&) = delete;
            RenderContext& operator=(const RenderContext&) = delete;

            RenderContext(RenderContext&&) noexcept = default;
            RenderContext& operator=(RenderContext&&) noexcept = default;

            UniformBuffer cameraUniformBuffer;
            UniformBuffer frameUniformBuffer;
            
            uint32_t width = 0;
            uint32_t height = 0;


    };

}; // Renderer
