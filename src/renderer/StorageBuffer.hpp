#pragma once

#include <cstddef>
#include <span>

#include <glad/gl.h>


namespace Renderer
{

class StorageBuffer
{
public:
	StorageBuffer();
	~StorageBuffer();

	void Reserve(size_t byteSize, GLenum usage = GL_DYNAMIC_DRAW)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Handle);
		glBufferData(GL_SHADER_STORAGE_BUFFER, byteSize, nullptr, usage);
		m_AllocatedSize = byteSize;
	}

	template<typename T>
	void Upload(std::span<const T> data, GLenum usage = GL_DYNAMIC_DRAW)
	{
		size_t byteSize = sizeof(T) * data.size();
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Handle);
		if (byteSize <= m_AllocatedSize)
		{
			// fits — no reallocation, no GPU sync stall
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, byteSize, data.data());
		}
		else
		{
			glBufferData(GL_SHADER_STORAGE_BUFFER, byteSize, data.data(), usage);
			m_AllocatedSize = byteSize;
		}
	}

	template<typename T>
	void Upload(const T& data, GLenum usage = GL_DYNAMIC_DRAW)
	{
		size_t byteSize = sizeof(T);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Handle);
		if(byteSize <= m_AllocatedSize)
		{
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, byteSize, &data);
		}
		else
		{
			glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T), &data, usage);
			m_AllocatedSize = byteSize;
		}
	};

	template<typename T>
	void Update(const T& data, GLintptr offset = 0)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Handle);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(T), &data);
	};

	template<typename T>
	void Update(const std::span<const T>& data, GLintptr offset = 0)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_Handle);
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, sizeof(T) * data.size(), data.data());
	};


	void Bind(GLuint bindingPoint) const;

	void Unbind() const;

private:
	unsigned int m_Handle;
    std::size_t m_AllocatedSize = 0;

};

}
