#include "CloudPass.hpp"

namespace Renderer
{

    CloudPass::CloudPass(const RenderContext& context)
        : m_CompShader("resources/shaders/CloudShader.comp")
    {
        m_Resources.setTexture(0, context.cloudNoiseTexture);
        m_Resources.setImage(0, context.outputTexture, ImageAccess::WriteOnly);

        m_Resources.setUniformBuffer(0, context.cameraUniformBuffer);
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
} // Renderer
