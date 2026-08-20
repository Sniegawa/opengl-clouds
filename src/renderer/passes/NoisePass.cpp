#include "NoisePass.hpp"


namespace Renderer
{
    
    NoisePass::NoisePass(const RenderContext& context)
        : m_CompShader("resources/shaders/NoiseGenerator.comp")
    {
        m_Resources.setImage(0, context.NoiseTexture, ImageAccess::WriteOnly);
    }

    void NoisePass::execute(RenderContext& context)
    {
        m_CompShader.bind();
        m_Resources.bind();

        m_CompShader.dispatch(
                (static_cast<float>(context.NoiseTexture.getWidth())+15.0) / 16.0,
                (static_cast<float>(context.NoiseTexture.getHeight())+15.0) / 16.0,
                1
        );
    }


}
