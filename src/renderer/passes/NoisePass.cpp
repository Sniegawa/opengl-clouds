#include "NoisePass.hpp"
#include "imgui.h"
#include <iterator>


namespace Renderer
{
    
    NoisePass::NoisePass(const RenderContext& context)
        : m_CompShader("resources/shaders/NoiseGenerator.comp")
    {
        m_Resources.setImage(0, context.cloudNoiseTexture, ImageAccess::WriteOnly);
        m_Resources.setImage(1, context.cloudDetailTexture, ImageAccess::WriteOnly);
        m_Resources.setUniformBuffer(1, context.NoiseSettingsBuffer);


        m_Data = MakeDefaultNoiseData();
    }

    // TODO: make this execute only once on startup, and eventually on settings tweak
    void NoisePass::execute(RenderContext& context)
    {
        m_CompShader.bind();
        m_Resources.bind();

        m_CompShader.dispatch(
                (static_cast<float>(context.cloudNoiseTexture.getWidth()) + 7.0) / 8.0,
                (static_cast<float>(context.cloudNoiseTexture.getHeight()) + 7.0) / 8.0,
                (static_cast<float>(context.cloudNoiseTexture.getDepth()) + 7.0) / 8.0
        );
    }

    void NoisePass::onImGui(RenderContext& context)
    {
        ImGui::Begin("Noise pass");


        NoiseData& data = m_Data;

        int i = 0;
        for(auto& channel : data.noiseChannels)
        {
            i++;
            ImGui::PushID(i);
            ImGui::DragFloat("Cells", &channel.cells,0.1f,4.0f,1024.0f);
            
            ImGui::DragInt("Octaves", &channel.octaves,0.1f,1,16);

            ImGui::DragFloat("Seed", &channel.seed);
            
            ImGui::Spacing();

            ImGui::PopID();
        }
        
        if(ImGui::Button("Regenerate Noise"))
        {
            context.NoiseSettingsBuffer.update(&data, sizeof(NoiseData));
            context.RegenNoise = true;
        }

        ImGui::End();
    }
}

