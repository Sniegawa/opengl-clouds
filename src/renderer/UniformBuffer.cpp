#include "UniformBuffer.hpp"

#include <glad/gl.h>

namespace Renderer
{
    UniformBuffer::UniformBuffer()
    {
        glGenBuffers(1, &m_Handle);
    }

    UniformBuffer::~UniformBuffer()
    {
        glDeleteBuffers(1, &m_Handle);
    }

    void UniformBuffer::setData(const void* data, std::size_t size)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
        glBufferData(GL_UNIFORM_BUFFER, size, data, GL_DYNAMIC_DRAW);
    }

    void UniformBuffer::update(const void* data, std::size_t size, std::size_t offset)
    {
        glBindBuffer(GL_UNIFORM_BUFFER, m_Handle);
        glBufferSubData(GL_UNIFORM_BUFFER, offset, size, data);
    }

    void UniformBuffer::bind(uint32_t binding) const
    {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, m_Handle);
    }

    uint32_t UniformBuffer::getHandle() const { return m_Handle; }

}; // Renderer
