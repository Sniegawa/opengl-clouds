#include "CloudPass.hpp"
#include "imgui.h"
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <glm/gtc/type_ptr.hpp>

namespace Renderer
{

    CloudPass::CloudPass(const RenderContext& context)
        : m_CompShader("resources/shaders/CloudShader.comp")
    {
        m_Resources.setTexture(0, context.cloudNoiseTexture);
        m_Resources.setTexture(1, context.cloudDetailTexture);
        m_Resources.setTexture(2, context.cloudMask);
        m_Resources.setImage(0, context.outputTexture, ImageAccess::WriteOnly);

        m_Resources.setUniformBuffer(0, context.cameraUniformBuffer);
        m_Resources.setUniformBuffer(2, context.cloudSettingsBuffer);
        m_Resources.setUniformBuffer(1, context.frameUniformBuffer);
    }

    void CloudPass::execute(RenderContext& context)
    {
        m_CompShader.bind();
        m_Resources.bind();


        m_CompShader.dispatch(
                (static_cast<float>(context.width) + 15.0) / 16.0,
                (static_cast<float>(context.height) + 15.0) / 16.0,
                1);
    }

    void CloudPass::onImGui(RenderContext& context) 
    {
        ImGui::Begin("Cloud Settings");

        CloudData& data = m_Data;
        bool flag = false;


        if(ImGui::DragFloat3("Box Min", glm::value_ptr(data.BoxMin),0.1f)) flag = true;
        if(ImGui::DragFloat3("Box Max", glm::value_ptr(data.BoxMax),0.1f)) flag = true;


        if(ImGui::DragFloat3("Sun Direction", glm::value_ptr(data.SunDir),0.01f,-1.0f,1.0f)) flag = true;
        if(ImGui::ColorEdit3("Sun Color", glm::value_ptr(data.SunColor))) flag = true;

        if(ImGui::DragFloat("Sun Intensity", &data.SunIntensity, 0.1f)) flag = true;

        ImGui::Spacing();

        
        if(ImGui::DragFloat("Shape Scale", &data.ShapeNoiseScale,0.001f,0.0001f,5.0f)) flag = true;
        if(ImGui::DragFloat3("ShapeOffset", glm::value_ptr(data.ShapeOffset),0.1f)) flag = true;
        if(ImGui::DragFloat("Shape Offset Speed", &data.ShapeOffsetSpeed,0.001f,0.0)) flag = true;


        ImGui::Spacing();

        
        if(ImGui::DragFloat("Detail Scale", &data.DetailNoiseScale,0.001f,0.0001f,5.0f)) flag = true;
        if(ImGui::DragFloat3("DetailOffset", glm::value_ptr(data.DetailOffset),0.1f)) flag = true;
        if(ImGui::DragFloat("Detail Offset Speed", &data.DetailOffsetSpeed)) flag = true;

        ImGui::Spacing();

        if(ImGui::ColorEdit3("CloudColor", glm::value_ptr(data.CloudColor))) flag = true;

        if(ImGui::DragFloat("Absorption", &data.Absorption, 0.05f, 0.01f, 50.0f)) flag = true;

        if(ImGui::DragFloat("LightAbsorption", &data.LightAbsorption, 0.01f, 0.001f, 50.0f)) flag = true;

        if(ImGui::DragInt("MaxSteps", &data.MaxSteps, 1.0f, 10, 500)) flag = true;

        if(ImGui::DragInt("LightSteps", &data.LightSteps, 0.01f, 1, 50)) flag = true;

        if(ImGui::DragFloat("Erosion Factor", &data.ErosionFactor , 0.01f, 0.0f, 1.0f)) flag = true;
        if(ImGui::DragFloat("LightStepSize", &data.LightStepSize, 0.01f, 0.01f, 4.0f)) flag = true;


        if(flag)
            context.cloudSettingsBuffer.update(&data, sizeof(CloudData));
    


        ImGui::End();


        ImGui::Begin("Mask",NULL, ImGuiWindowFlags_NoMove);

        static int BrushSize = 16;
        static float BrushStrength = 2.0f;

        const ImVec2 canvasSize = ImVec2(512,512);
        uint32_t TextureSize = context.cloudMask.getWidth(); // Mask will always be a square
        float scale = static_cast<float>(TextureSize) / canvasSize.x;

        static std::vector<uint8_t> maskBuffer(TextureSize * TextureSize, 0); // Todo move it somewhere 


        unsigned int maskID = context.cloudMask.getHandle();
        ImVec2 canvasPos = ImGui::GetCursorScreenPos();
        ImGui::Image((ImTextureID)(uintptr_t)maskID,canvasSize,ImVec2(0,1),ImVec2(1,0));


        ImGuiIO& io = ImGui::GetIO();
        if(ImGui::IsItemHovered() && (ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDown(ImGuiMouseButton_Right)))
        {
           ImVec2 mousePos = io.MousePos;
           float localX = mousePos.x - canvasPos.x;
           float localY = mousePos.y - canvasPos.y;

           if(localX >= 0.0f && localX < canvasSize.x && localY >= 0.0f && localY < canvasSize.y)
           {
                int centerX = static_cast<int>(localX * scale);
                int centerY = static_cast<int>((canvasSize.y - localY) * scale);

                int brushRadius = BrushSize * static_cast<int>(scale);
                int minX = std::max(0, centerX - brushRadius);
                int minY = std::max(0, centerY - brushRadius);
                int maxX = std::min(static_cast<int>(TextureSize) - 1, centerX + brushRadius);
                int maxY = std::min(static_cast<int>(TextureSize) - 1, centerY + brushRadius);


                uint32_t regionWidth = static_cast<uint32_t>(maxX - minX + 1);
                uint32_t regionHeight = static_cast<uint32_t>(maxY - minY + 1);

                float sign = ImGui::IsMouseDown(ImGuiMouseButton_Right) ? -1.0f : 1.0f;

                std::vector<uint8_t> patch(regionWidth * regionHeight,0);
                for(int y = minY; y <= maxY; y++)
                {
                    for(int x = minX; x <= maxX; x++)
                    {
                        float dx = static_cast<float>(x - centerX);
                        float dy = static_cast<float>(y - centerY);
                        float dist = std::sqrt(dx * dx + dy * dy);

                        float t = dist / static_cast<float>(brushRadius);
                        float falloff = std::clamp(std::exp(-t * t * 4.0f) - 0.1f, 0.0f, 1.0f);
                        
                        size_t idx = static_cast<size_t>(y) * TextureSize + static_cast<size_t>(x);

                        float pps = io.DeltaTime * 400.0f;
                        float updated = std::clamp(static_cast<float>(maskBuffer[idx]) + sign * falloff * BrushStrength * pps, 0.0f, 255.0f);

                        uint8_t newValue = static_cast<uint8_t>(updated);
                        maskBuffer[idx] = newValue;
                        patch[(y - minY) * regionWidth + (x - minX)] = newValue;
                    }
                }

                context.cloudMask.setSubData(
                        static_cast<uint32_t>(minX),
                        static_cast<uint32_t>(minY),
                        regionWidth,
                        regionHeight,
                        patch.data(),
                        Format::Red,
                        DataType::UnsignedByte,
                        0
                );
           }


        }


        ImGui::DragInt("BrushSize", &BrushSize,1.0f,2,64);
        ImGui::DragFloat("Brush Strength", &BrushStrength, 0.5f, 1.0f, 16.0f);
        ImGui::End();


    }

} // Renderer
