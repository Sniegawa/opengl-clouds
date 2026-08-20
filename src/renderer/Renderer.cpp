#include "Renderer.hpp"
#include "passes/TestComputePass.hpp"

#include <glad/gl.h>

namespace Renderer
{

    Renderer::Renderer(uint32_t width, uint32_t height)
        :
        m_Context(width,height),
        m_TestPass(m_Context),
        m_FSQpass(m_Context.TestOutputTexture)
    {}


    Renderer::~Renderer()
    {

    }

    void Renderer::Render()
    {
        m_TestPass.execute(m_Context);
        m_FSQpass.execute(m_Context);
    }


    void Renderer::OnResize(uint32_t width, uint32_t height)
    {
        if(width == 0 || height == 0)
            return; // minimised

        if(width == m_Context.width && height == m_Context.height)
            return;

        m_Context.width = width;
        m_Context.height = height;

        m_Context.TestOutputTexture.Resize(width, height); 

        glViewport(0,0,width,height); // TODO: Move it elsewhere and keep glad out of this file
    }
}
