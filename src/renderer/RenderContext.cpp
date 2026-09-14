#include "RenderContext.hpp"
#include "TextureHelper.hpp"
#include <cstdlib>

namespace Renderer
{

    RenderContext::RenderContext(uint32_t width, uint32_t height)
        :
            width(width),height(height),
            cloudNoiseTexture(256,256,256,InternalFormat::RGBA8),
            cloudDetailTexture(64, 64, 64, InternalFormat::RGBA8),
            outputTexture(width, height, InternalFormat::RGBA16F),
            cloudMask(2048, 2048, InternalFormat::R8)
    {

        TextureFlags cloudMaskFlags;
        cloudMaskFlags.wrapS = TextureWrap::ClampToEdge;
        cloudMaskFlags.wrapT = TextureWrap::ClampToEdge;
        cloudMaskFlags.minFilter = TextureFilter::Linear;
        cloudMaskFlags.magFilter = TextureFilter::Linear;
        cloudMask.setFlags(cloudMaskFlags);
        {
            char* clearData = (char*)calloc(2048*2048, sizeof(char));
            cloudMask.setData(clearData, Format::Red, DataType::Byte);
        }

    }

    RenderContext::~RenderContext()
    {

    }

}// Renderer
