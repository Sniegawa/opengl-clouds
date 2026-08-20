#pragma once

#include "RenderContext.hpp"

#include "passes/TestComputePass.hpp"
#include "passes/FullScreenQuadPass.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Renderer
{
    
    class Renderer
    {
    public:
        Renderer(uint32_t width, uint32_t height);
        ~Renderer();

        void Render(); // Camera class goes here

        void OnResize(uint32_t width, uint32_t height);
    private:
        RenderContext m_Context;

        TestComputePass m_TestPass;

        FSQPass m_FSQpass;   

    };

}
