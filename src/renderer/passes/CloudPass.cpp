#include "CloudPass.hpp"
#include "imgui.h"
#include <glm/gtc/type_ptr.hpp>

namespace Renderer
{

    CloudPass::CloudPass(const RenderContext& context)
        : m_CompShader("resources/shaders/CloudShader.comp")
    {
        m_Resources.setTexture(0, context.cloudNoiseTexture);
        m_Resources.setTexture(1, context.cloudDetailTexture);
        m_Resources.setImage(0, context.outputTexture, ImageAccess::WriteOnly);

        m_Resources.setUniformBuffer(0, context.cameraUniformBuffer);
        m_Resources.setUniformBuffer(2, context.cloudSettingsBuffer);
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

        ImGui::Spacing();

        
        if(ImGui::DragFloat("Shape Scale", &data.ShapeNoiseScale,0.001f,0.0001f,5.0f)) flag = true;
        if(ImGui::DragFloat3("ShapeOffset", glm::value_ptr(data.ShapeOffset),0.1f)) flag = true;
        if(ImGui::DragFloat("Shape Offset Speed", &data.ShapeOffsetSpeed),0.01f) flag = true;


        ImGui::Spacing();

        
        if(ImGui::DragFloat("Detail Scale", &data.DetailNoiseScale,0.001f,0.0001f,5.0f)) flag = true;
        if(ImGui::DragFloat3("DetailOffset", glm::value_ptr(data.DetailOffset),0.1f)) flag = true;
        if(ImGui::DragFloat("Detail Offset Speed", &data.DetailOffsetSpeed)) flag = true;

        ImGui::Spacing();

        if(ImGui::ColorEdit3("CloudColor", glm::value_ptr(data.CloudColor))) flag = true;


        if(flag)
            context.cloudSettingsBuffer.update(&data, sizeof(CloudData));
    


        ImGui::End();
    }

} // Renderer
