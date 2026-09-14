#pragma once

#include <array>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/vector_float4.hpp>
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
        glm::vec3 CloudColor = glm::vec3(1.0f);
        float ShapeNoiseScale = 0.04f;

        glm::vec3 ShapeOffset = glm::vec3(0.0f);
        float ShapeOffsetSpeed = 0.0f;

        glm::vec3 DetailOffset = glm::vec3(0.0f);
        float DetailOffsetSpeed = 0.0f;

        glm::vec3 BoxMin = glm::vec3(-500.0f,-15.0f,-500.0f);
        float DetailNoiseScale = 1.0f;

        glm::vec3 BoxMax = glm::vec3(500.0f,15.0f,500.0f);
        float SunIntensity = 4.1f;

        glm::vec3 SunDir = glm::vec3(0.5f,0.8f,0.2f);
        float Absorption = 2.46f;

        glm::vec3 SunColor = glm::vec3(0.95f, 0.95f, 1.0f);
        float LightAbsorption = 1.29f;
        
        int MaxSteps = 100;
        int LightSteps = 8; // A bit laggy
        float ErosionFactor = 0.54f;
        float LightStepSize = 1.61f;

    };

    struct NoiseChannelParams
    {
        float cells   = 4.0f;
        int32_t octaves = 3;
        float seed    = 0.0f;
        float _pad    = 0.0f;
    };

    struct NoiseData
    {
        std::array<NoiseChannelParams, 7> noiseChannels;
    };

    inline NoiseData MakeDefaultNoiseData()
    {
        NoiseData data;
        data.noiseChannels =
        {{
            { 6.0f, 4, 1.0f, 0.0f }, // mainR
            { 4.0f, 2, 2.0f, 0.0f }, // mainG
            { 16.0f, 4, 3.0f, 0.0f }, // mainB
            { 32.0f, 4, 4.0f, 0.0f }, // mainA
            { 20.0f, 2, 5.0f, 0.0f }, // detailR
            { 24.0f, 3, 6.0f, 0.0f }, // detailG
            { 60.0f, 2, 7.0f, 0.0f }  // detailB
        }};
        return data;
    }

    
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
            Texture cloudDetailTexture;

            UniformBuffer cloudSettingsBuffer;
            
            // Noise

            bool RegenNoise = true;
            UniformBuffer NoiseSettingsBuffer;

            Texture outputTexture;

            uint32_t width = 0;
            uint32_t height = 0;


    };

}; // Renderer
