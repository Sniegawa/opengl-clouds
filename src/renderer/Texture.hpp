#pragma once

#include "TextureHelper.hpp"

#include <cstdint>

namespace Renderer
{
    
    

    class Texture
    {
        public:
            // 2D Texure constructor
            Texture(uint32_t width, uint32_t height, InternalFormat internalFormat);

            // 3D Texture constructor
            Texture(uint32_t width, uint32_t height, uint32_t depth, InternalFormat internalFormat);
            ~Texture();

            void bind(uint32_t unit) const;
            void bindImage(uint32_t unit, ImageAccess access) const; 


            void setData(const void* data, Format format, DataType dataType);

            // Texture2D function to setSubData
            void setSubData(
                    uint32_t x, uint32_t y,
                    uint32_t width, uint32_t height,
                    const void* data,
                    Format format, DataType dataType,
                    uint32_t mipLevel = 0
            );

            // Texture3D function to setSubData
            void setSubData(
                    uint32_t x, uint32_t y, uint32_t z,
                    uint32_t width, uint32_t height, uint32_t depth,
                    const void* data,
                    Format format, DataType dataType,
                    uint32_t mipLevel = 0
            );

            void Resize(uint32_t width, uint32_t height, uint32_t depth = 1);

            unsigned int getHandle() const;
            TextureType getTargetType() const;

            uint32_t getWidth() const;
            uint32_t getHeight() const;
            uint32_t getDepth() const;


            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;

            Texture(Texture&&) noexcept = default;
            Texture& operator=(Texture&&) noexcept = default;


        private:
            unsigned int m_Handle;
            TextureType m_Target;
            InternalFormat m_InternalFormat;
            uint32_t m_Width, m_Height, m_Depth;

    };

}
