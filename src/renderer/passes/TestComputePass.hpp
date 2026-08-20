#pragma once

#include "RenderPass.hpp"

#include "../RenderContext.hpp"
#include "../ComputeShader.hpp"
#include "../ShaderResources.hpp"

namespace Renderer
{
    class TestComputePass : public RenderPass
    {
    public:

        TestComputePass(RenderContext& context);

        void execute(RenderContext& context) override;

    private:
        ComputeShader m_CompShader;
    
        ShaderResources m_Resources;

        uint32_t m_Width, m_Height;
    };


}
