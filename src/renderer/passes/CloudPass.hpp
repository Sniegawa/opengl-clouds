#pragma once

#include "RenderPass.hpp"

#include "../RenderContext.hpp"
#include "../ComputeShader.hpp"
#include "../ShaderResources.hpp"

namespace Renderer
{
    class CloudPass : public RenderPass
    {
    public:
       CloudPass(const RenderContext& context);

       void execute(RenderContext& context) override;

       void onImGui(RenderContext& context) override;

    private:
       ComputeShader m_CompShader;
       ShaderResources m_Resources;

       CloudData m_Data;
    };
}
