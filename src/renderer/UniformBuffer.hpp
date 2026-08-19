#pragma once

#include <cstdint>
#include <cstddef>

namespace Renderer
{
    class UniformBuffer
    {
    public:
        UniformBuffer();
        ~UniformBuffer();

        UniformBuffer(const UniformBuffer&) = delete;
        UniformBuffer& operator=(const UniformBuffer&) = delete;

        UniformBuffer(UniformBuffer&& other) noexcept;
        UniformBuffer& operator=(UniformBuffer&& other) noexcept;

        void setData(const void* data, std::size_t size);
        void update(const void* data, std::size_t size, std::size_t offset = 0);

        void bind(uint32_t binding) const;

        uint32_t getHandle() const;

    private:
        uint32_t m_Handle = 0;

    };
}
