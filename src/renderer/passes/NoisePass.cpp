#include "NoisePass.hpp"


namespace Renderer
{
    
    NoisePass::NoisePass(const RenderContext& context)
        : m_CompShader("resources/shaders/NoiseGenerator.comp")
    {
        m_Resources.setImage(0, context.cloudNoiseTexture, ImageAccess::WriteOnly);
        m_Resources.setImage(1, context.cloudDetailTexture, ImageAccess::WriteOnly);
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
}
