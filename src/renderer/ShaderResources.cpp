#include "ShaderResources.hpp"

#include "StorageBuffer.hpp"
#include "UniformBuffer.hpp"
#include "Texture.hpp"

namespace Renderer
{

    void ShaderResources::setUniformBuffer(uint32_t binding, const UniformBuffer& buffer)
    {
        for(auto& resource : m_UniformBuffers)
        {
            if(resource.binding == binding)
            {
                resource.buffer = &buffer;
                return;
            }
        }

        m_UniformBuffers.push_back({ binding, &buffer });
    }

    void ShaderResources::setStorageBuffer(uint32_t binding, const StorageBuffer& buffer)
    {
        for(auto& resource : m_StorageBuffers)
        {
            if(resource.binding == binding)
            {
                resource.buffer = &buffer;
                return;
            }
        }

        m_StorageBuffers.push_back({ binding, &buffer });    
    }

    void ShaderResources::setTexture(uint32_t unit, const Texture& texture)
    {
        for(auto& resource : m_Textures)
        {
            if(resource.unit == unit)
            {
                resource.texture = &texture;
                return;
            }
        }

        m_Textures.push_back({ unit, &texture });
    }

    void ShaderResources::setImage(uint32_t unit, const Texture& texture, ImageAccess access)
    {
        for(auto& resource : m_Images)
        {
            if(resource.unit == unit)
            {
                resource.texture = &texture;
                resource.access = access;
                return;
            }
        }

        m_Images.push_back({ unit, &texture, access });       
    }

    void ShaderResources::bind() const
    {
        for(const auto& resource : m_UniformBuffers)
        {
            resource.buffer->bind(resource.binding);
        }
        
        for(const auto& resource : m_StorageBuffers)
        {
            resource.buffer->Bind(resource.binding);
        }

        for(const auto& resource : m_Textures)
        {
            resource.texture->bind(resource.unit);
        }

        for(const auto& resource : m_Images)
        {
            resource.texture->bindImage(resource.unit, resource.access);
        }
    }

}
