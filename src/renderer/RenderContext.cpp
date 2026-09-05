#include "RenderContext.hpp"
#include "TextureHelper.hpp"

namespace Renderer
{

    RenderContext::RenderContext(uint32_t width, uint32_t height)
        :
            width(width),height(height),
            cloudNoiseTexture(128,128,128,InternalFormat::RGBA8),
            cloudDetailTexture(32, 32, 32, InternalFormat::RGBA8),
            outputTexture(width, height, InternalFormat::RGBA16F)
    {}

    RenderContext::~RenderContext()
    {

    }

}// Renderer
