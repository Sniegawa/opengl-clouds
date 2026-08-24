#include "RenderContext.hpp"
#include "TextureHelper.hpp"

namespace Renderer
{

    RenderContext::RenderContext(uint32_t width, uint32_t height)
        :
            width(width),height(height),
            cloudNoiseTexture(124,124,124,InternalFormat::RGBA8),
            outputTexture(width, height, InternalFormat::RGBA16F)
    {}

    RenderContext::~RenderContext()
    {

    }

}// Renderer
