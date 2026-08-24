#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include "UniformBuffer.hpp"

#include "Texture.hpp"

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

    struct CloudData
    {
        glm::vec3 CloudColor = glm::vec3(0.9f);
        float Density = 0.0f;
    };

    
    class RenderContext
    {
        public:
            RenderContext(uint32_t width, uint32_t height);
            ~RenderContext();

            RenderContext(const RenderContext&) = delete;
            RenderContext& operator=(const RenderContext&) = delete;

            RenderContext(RenderContext&&) noexcept = default;
            RenderContext& operator=(RenderContext&&) noexcept = default;

            UniformBuffer cameraUniformBuffer;
            UniformBuffer frameUniformBuffer;

            // Cloud
            Texture cloudNoiseTexture;
            UniformBuffer cloudSettingsBuffer;
            


            Texture outputTexture;

            uint32_t width = 0;
            uint32_t height = 0;


    };

}; // Renderer
