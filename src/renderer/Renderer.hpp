#pragma once

#include "RenderContext.hpp"

#include "passes/CloudPass.hpp"
#include "passes/FullScreenQuadPass.hpp"
#include "passes/NoisePass.hpp"

#include "../camera.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Renderer
{
    
    class Renderer
    {
    public:
        Renderer(uint32_t width, uint32_t height);
        ~Renderer();

        void Render(const Camera& camera); // Camera class goes here

        void OnResize(uint32_t width, uint32_t height);
    private:
        RenderContext m_Context;

        NoisePass m_NoisePass;

        CloudPass m_CloudPass;

        FSQPass m_FSQpass;   

    };

}
