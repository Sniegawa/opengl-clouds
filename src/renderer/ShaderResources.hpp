#pragma once

#include <vector>

#include <cstdint>
#include "TextureHelper.hpp"

namespace Renderer
{
    
    class Texture;
    class UniformBuffer;
    class StorageBuffer;
 
    class ShaderResources 
    {
    public:
        void setUniformBuffer(uint32_t binding, const UniformBuffer& buffer);
        void setStorageBuffer(uint32_t binding, const StorageBuffer& buffer);
        void setTexture(uint32_t unit, const Texture& texture);
        void setImage(uint32_t unit, const Texture& texture, ImageAccess access);

        void bind() const;

    private:
    
        struct UniformBufferBinding
        {
            uint32_t binding;
            const UniformBuffer* buffer;
        };

        struct StorageBufferBinding
        {
            uint32_t binding;
            const StorageBuffer* buffer;
        };

        struct TextureBinding
        {
            uint32_t unit;
            const Texture* texture;
        };

        struct ImageBinding
        {
            uint32_t unit;
            const Texture* texture;
            ImageAccess access;
        };

        std::vector<UniformBufferBinding> m_UniformBuffers;
        std::vector<StorageBufferBinding> m_StorageBuffers;
        std::vector<TextureBinding> m_Textures;
        std::vector<ImageBinding> m_Images;

    };
} // Renderer
