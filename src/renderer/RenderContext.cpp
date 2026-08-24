#include "RenderContext.hpp"
#include "TextureHelper.hpp"

namespace Renderer
{

    RenderContext::RenderContext(uint32_t width, uint32_t height)
        :
            width(width),height(height),
            cloudNoiseTexture(512,512,512,InternalFormat::RGBA8),
            cloudDetailTexture(256, 256, 256, InternalFormat::RGBA8),
            outputTexture(width, height, InternalFormat::RGBA16F)
    {}

    RenderContext::~RenderContext()
    {

    }

}// Renderer
