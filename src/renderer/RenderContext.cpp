#include "RenderContext.hpp"
#include "TextureHelper.hpp"

namespace Renderer
{

    RenderContext::RenderContext(uint32_t width, uint32_t height)
        :
           width(width),height(height),
           NoiseTexture(2048,2048,InternalFormat::RGBA16F)
    {}

    RenderContext::~RenderContext()
    {

    }

}// Renderer
