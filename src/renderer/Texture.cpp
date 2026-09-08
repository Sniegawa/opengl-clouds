#include "Texture.hpp"
#include "TextureHelper.hpp"


#include <glad/gl.h>


#include <iostream>

namespace Renderer
{
    Texture::Texture(uint32_t width, uint32_t height, InternalFormat internalFormat, TextureFlags flags)
        : 
        m_Handle(0),
        m_Width(width), 
        m_Height(height),
        m_Depth(1), 
        m_Target(TextureType::Texture2D),
        m_InternalFormat(internalFormat)
    {
        glCreateTextures(Helper::ToGL(m_Target), 1, &m_Handle);

        glTextureStorage2D(
                m_Handle,
                1,
                Helper::ToGL(internalFormat),
                m_Width,
                m_Height
        );        

        setFlags(flags);
    }

    Texture::Texture(uint32_t width, uint32_t height, uint32_t depth, InternalFormat internalFormat, TextureFlags flags)
        :
        m_Handle(0),
        m_Width(width), 
        m_Height(height),
        m_Depth(depth), 
        m_Target(TextureType::Texture3D),
        m_InternalFormat(internalFormat)
    {
        glCreateTextures(Helper::ToGL(m_Target), 1, &m_Handle);

        glTextureStorage3D(
            m_Handle,
            1,
            Helper::ToGL(internalFormat),
            m_Width,
            m_Height,
            m_Depth
        );        

        setFlags(flags);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_Handle);
    }

    void Texture::setFlags(TextureFlags flags)
    {
        glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_S, Helper::ToGL(flags.wrapS));
        glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_T, Helper::ToGL(flags.wrapT));
        glTextureParameteri(m_Handle, GL_TEXTURE_WRAP_R, Helper::ToGL(flags.wrapR));

        glTextureParameteri(m_Handle, GL_TEXTURE_MIN_FILTER, Helper::ToGL(flags.minFilter));
        glTextureParameteri(m_Handle, GL_TEXTURE_MAG_FILTER, Helper::ToGL(flags.magFilter));
        GLint swizzle[4];
        glGetTextureParameteriv(m_Handle, GL_TEXTURE_SWIZZLE_RGBA, swizzle);

        int a = 0;
    }


    void Texture::bind(uint32_t unit) const
    {
        glBindTextureUnit(unit,m_Handle);
    }

    void Texture::bindImage(uint32_t unit, ImageAccess access) const
    {
        if(m_Target == TextureType::Texture2D)
        {
            glBindImageTexture(
                unit,
                m_Handle,
                0,
                false,
                0,
                Helper::ToGL(access),
                Helper::ToGL(m_InternalFormat)
            );
        }
        else if(m_Target == TextureType::Texture3D)
        {
             glBindImageTexture(
                unit,
                m_Handle,
                0,
                GL_TRUE,
                0,
                Helper::ToGL(access),
                Helper::ToGL(m_InternalFormat)
            );           
        }
    }



    void Texture::setData(const void* data, Format format, DataType dataType)
    {
        switch(m_Target)
        {
        case TextureType::Texture2D:
            setSubData(0,0,m_Width,m_Height,data,format,dataType);
            break;
        case TextureType::Texture3D:
            setSubData(0,0,0,m_Width,m_Height,m_Depth,data,format,dataType);
            
            break;
        default:
            std::cout<<"SetData isn't implemented for given Texture Type" << std::endl;
        }
    }

    void Texture::setSubData(uint32_t x, uint32_t y, uint32_t width, uint32_t height, const void* data, Format format, DataType dataType, uint32_t mipLevel)
    {
        glTextureSubImage2D(
                m_Handle,
                mipLevel,
                x,
                y,
                width,
                height,
                Helper::ToGL(format),
                Helper::ToGL(dataType),
                data
        );
    }
    void Texture::setSubData(uint32_t x, uint32_t y, uint32_t z, uint32_t width, uint32_t height, uint32_t depth, const void* data, Format format, DataType dataType, uint32_t mipLevel)
    {
        glTextureSubImage3D(
                m_Handle,
                mipLevel,
                x,
                y,
                z,
                width,
                height,
                depth,
                Helper::ToGL(format),
                Helper::ToGL(dataType),
                data
        );
    }

    void Texture::Resize(uint32_t width, uint32_t height, uint32_t depth)
    {
        if(m_Width == width && m_Height == height && m_Depth == depth)
            return;

        m_Width = width;
        m_Height = height;
        m_Depth = depth;

        glDeleteTextures(1, &m_Handle);

        glCreateTextures(
                Helper::ToGL(m_Target),
                1,
                &m_Handle
        );

        if(m_Target == TextureType::Texture2D)
        {
            glTextureStorage2D(
                    m_Handle,
                    1,
                    Helper::ToGL(m_InternalFormat),
                    m_Width,
                    m_Height
            );
        }
        else if(m_Target == TextureType::Texture3D)
        {
            glTextureStorage3D(
                    m_Handle,
                    1,
                    Helper::ToGL(m_InternalFormat),
                    m_Width,
                    m_Height,
                    m_Depth
            );
        }

    }


    // GETTERS

    unsigned int Texture::getHandle() const { return m_Handle; }
    TextureType Texture::getTargetType() const { return m_Target; }

    uint32_t Texture::getWidth() const { return m_Width; }
    uint32_t Texture::getHeight() const { return m_Height; }
    uint32_t Texture::getDepth() const { return m_Depth; }

    

}; // Renderer
