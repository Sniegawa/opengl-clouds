#include "StorageBuffer.hpp"

#include "glad/gl.h"

namespace Renderer
{

    StorageBuffer::StorageBuffer()
    {
        glGenBuffers(1,&m_Handle);
    }

    StorageBuffer::~StorageBuffer()
    {
        glDeleteBuffers(1,&m_Handle);
    }

    void StorageBuffer::Bind(GLuint bindingPoint) const 
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, bindingPoint);
    }

    void StorageBuffer::Unbind() const 
    {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }


};
